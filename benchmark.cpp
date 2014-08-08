/**
 * Written(W) 2014 Abinash Panda
 * Copyright(C) 2014 Abinash Panda
 */

#include <shogun/base/init.h>
#include <shogun/io/SGIO.h>
#include <shogun/mathematics/Math.h>
#include <shogun/features/SparseFeatures.h>
#include <shogun/structure/MultilabelSOLabels.h>
#include <shogun/structure/MultilabelModel.h>
#include <shogun/structure/MultilabelCLRModel.h>
#include <shogun/structure/HashedMultilabelModel.h>
#include <shogun/structure/HierarchicalMultilabelModel.h>
#include <shogun/structure/StochasticSOSVM.h>
#include <shogun/lib/Time.h>

using namespace shogun;

/** generating random sparse features
 */
CSparseFeatures<float64_t> * generate_features(int32_t dim_features,
                int32_t num_samples)
{
	SGSparseMatrix<float64_t> feats(dim_features, num_samples);

	/** as the features are sparse, so number of features would be
	 * 1/10th of the dimension of feature space
	 */
	int32_t num_features = dim_features / 10;

	for (index_t i = 0; i < num_samples; i++)
	{
		feats[i] = SGSparseVector<float64_t>(dim_features);

		for (index_t j = 0; j < num_features; j++)
		{
			feats[i].features[j].feat_index = CMath::random(0, dim_features - 1);
			feats[i].features[j].entry = CMath::random(-100, 100);
		}

		feats[i].sort_features();
	}

	CSparseFeatures<float64_t> * features = new CSparseFeatures<float64_t>(feats);
	SG_REF(features);

	return features;

}

/** generating random sparse multilabels
 */
CMultilabelSOLabels * generate_labels(int32_t num_classes, int32_t num_samples)
{
	SGVector<int32_t> * labs = SG_MALLOC(SGVector<int32_t>, num_samples);

	SGVector<int32_t> classes(num_classes);
	classes.range_fill(0);

	for (index_t i = 0; i < num_samples; i++)
	{
		classes.randperm();
		int32_t num_labels = CMath::random(1, num_classes);

		SGVector<int32_t> label(num_labels);

		for (index_t j = 0; j < num_labels; j++)
		{
			label[j] = classes[j];
		}
	}

	CMultilabelSOLabels * labels = new CMultilabelSOLabels(num_samples,
	                num_classes);
	SG_REF(labels);
	labels->set_sparse_labels(labs);

	return labels;
}

/** Testing the model using StochasticSOSVM machine
 */
void test_model(CStructuredModel * model, CStructuredLabels * labels)
{
	CStochasticSOSVM * sgd = new CStochasticSOSVM(model, labels, true, true);
	SG_REF(sgd);

	/** running for only 1 iteration */
	sgd->set_num_iter(1);

	CTime * start = new CTime();
	SG_REF(start);
	sgd->train();
	float64_t t1 = start->cur_time_diff(false);

	SG_SPRINT(">>> Time taken for training using %s of %s = %f\n",
	          sgd->get_name(), model->get_name(), t1);

	SG_UNREF(start);
	SG_UNREF(sgd);
}

void test_multilabel_model(int32_t num_classes, int32_t num_feats,
                           int32_t num_samples)
{
	CSparseFeatures<float64_t> * features = generate_features(num_feats,
	                                        num_samples);

	CMultilabelSOLabels * labels = generate_labels(num_classes, num_samples);

	CMultilabelModel * model = new CMultilabelModel(features, labels);
	SG_REF(model);

	test_model(model, labels);

	SG_UNREF(model);
	SG_UNREF(labels);
	SG_UNREF(features);
}

void test_multilabel_clr_model(int32_t num_classes, int32_t num_feats,
                               int32_t num_samples)
{
	CSparseFeatures<float64_t> * features = generate_features(num_feats,
	                                        num_samples);

	CMultilabelSOLabels * labels = generate_labels(num_classes, num_samples);

	CMultilabelCLRModel * model = new CMultilabelCLRModel(features, labels);
	SG_REF(model);

	test_model(model, labels);

	SG_UNREF(model);
	SG_UNREF(labels);
	SG_UNREF(features);
}

void test_hashed_multilabel_model(int32_t num_classes, int32_t num_feats,
                                  int32_t num_samples)
{
	CSparseFeatures<float64_t> * features = generate_features(num_feats,
	                                        num_samples);

	CMultilabelSOLabels * labels = generate_labels(num_classes, num_samples);

	int32_t hash_dims = (num_classes * num_feats) / 10;

	CHashedMultilabelModel * model = new CHashedMultilabelModel(features,
	                labels, hash_dims);
	SG_REF(model);

	test_model(model, labels);

	SG_UNREF(model);
	SG_UNREF(labels);
	SG_UNREF(features);
}

void test_hierarchical_multilabel_model(int32_t num_classes, int32_t num_feats,
                                        int32_t num_samples)
{
	CSparseFeatures<float64_t> * features = generate_features(num_feats,
	                                        num_samples);

	CMultilabelSOLabels * labels = generate_labels(num_classes, num_samples);

	SGVector<int32_t> taxonomy(num_classes);
	taxonomy.range_fill(-1);

	CHierarchicalMultilabelModel * model = new CHierarchicalMultilabelModel(
	        features, labels, taxonomy);
	SG_REF(model);

	test_model(model, labels);

	SG_UNREF(model);
	SG_UNREF(labels);
	SG_UNREF(features);
}

int main(int argc, char ** argv)
{
	init_shogun_with_defaults();

	if (argc < 4)
	{
		SG_SERROR("Usage: benchmark <model> <num_classes> <num_feats> <num_samples>\n");
	}

	int32_t num_classes = ::atoi(argv[2]);
	int32_t num_feats = ::atoi(argv[3]);
	int32_t num_samples = ::atoi(argv[4]);

	if (!strcmp(argv[1], "MultilabelModel"))
	{
		test_multilabel_model(num_classes, num_feats, num_samples);
	}
	else if (!strcmp(argv[1], "HashedMultilabelModel"))
	{
		test_hashed_multilabel_model(num_classes, num_feats, num_samples);
	}
	else if (!strcmp(argv[1], "MultilabelCLRModel"))
	{
		test_multilabel_clr_model(num_classes, num_feats, num_samples);
	}
	else if (!strcmp(argv[1], "HierarchicalMultilabelModel"))
	{
		test_hierarchical_multilabel_model(num_classes, num_feats, num_samples);
	}
	else
	{
		SG_SERROR("<model> can be only among MultilabelModel/MultilabelCLRModel/"
		          "HashedMultilabelModel/HierarchicalMultilabelModel\n");
	}

	exit_shogun();

	return 0;
}

