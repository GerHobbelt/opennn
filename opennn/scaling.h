//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   S T A T I S T I C S   H E A D E R
//
//   Artificial Intelligence Techniques, SL
//   artelnics@artelnics.com

#ifndef SCALING_H
#define SCALING_H

// System includes

#include <fstream>
#include <iostream>
#include <limits>
#include <math.h>
#include <vector>

// OpenNN includes

#include "config.h"
#include "statistics.h"

using namespace std;
using namespace Eigen;

namespace OpenNN
{
/// Enumeration of available methods for scaling and unscaling the data.

enum Scaler{NoScaling, NoUnscaling, MinimumMaximum, MeanStandardDeviation, StandardDeviation, Logarithm};

void scale_mean_standard_deviation(Tensor<type, 2>&, const Index&, const Descriptives&);
void scale_standard_deviation(Tensor<type, 2>&, const Index&, const Descriptives&);
void scale_minimum_maximum(Tensor<type, 2>&, const Index&, const Descriptives&);
void scale_logarithmic(Tensor<type, 2>&, const Index&, const Descriptives&);
void scale_minimum_maximum_binary(Tensor<type, 2>&, const type&, const type&, const Index&);


void unscale_minimum_maximum(Tensor<type, 2>&, const Index&, const Descriptives&);
void unscale_mean_standard_deviation(Tensor<type, 2>&, const Index&, const Descriptives&);
void unscale_standard_deviation(Tensor<type, 2>&, const Index&, const Descriptives&);
void unscale_logarithmic(Tensor<type, 2>&, const Index&, const Descriptives&);

}

#endif // STATISTICS_H
