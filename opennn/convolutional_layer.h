//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   C O N V O L U T I O N A L   L A Y E R   C L A S S   H E A D E R
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#ifndef CONVOLUTIONALLAYER_H
#define CONVOLUTIONALLAYER_H

// System includes

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <ctype.h>
#include <stdexcept>

// OpenNN includes

#include "layer.h"
#include "config.h"
#include "probabilistic_layer.h"
#include "flatten_layer.h"
#include "pooling_layer.h"

namespace opennn
{

struct ConvolutionalLayerForwardPropagation;
struct ConvolutionalLayerBackPropagation;

#ifdef OPENNN_CUDA
    struct ConvolutionalLayerForwardPropagationCuda;
#endif

class ConvolutionalLayer : public Layer
{

public:

    /// Enumeration of the available activation functions for the convolutional layer.

    enum class ActivationFunction{Threshold,
                                  SymmetricThreshold,
                                  Logistic,
                                  HyperbolicTangent,
                                  Linear,
                                  RectifiedLinear,
                                  ExponentialLinear,
                                  ScaledExponentialLinear,
                                  SoftPlus,
                                  SoftSign,
                                  HardSigmoid};

    enum class ConvolutionType{Valid, Same};

    // Constructors

    explicit ConvolutionalLayer();

    explicit ConvolutionalLayer(const Index&, const Index&, const ActivationFunction& = ConvolutionalLayer::ActivationFunction::Linear);

    explicit ConvolutionalLayer(const Tensor<Index, 1>&, const Tensor<Index, 1>&);

    // Destructor

    // Get methods

    bool is_empty() const;

    const Tensor<type, 1>& get_biases() const;

    const Tensor<type, 4>& get_synaptic_weights() const;

    Index get_biases_number() const;

    Index get_synaptic_weights_number() const;

    ActivationFunction get_activation_function() const;

    string write_activation_function() const;

    Tensor<Index, 1> get_inputs_dimensions() const;
    Tensor<Index, 1> get_outputs_dimensions() const;

    Index get_outputs_rows_number() const;

    Index get_outputs_columns_number() const;

    ConvolutionType get_convolution_type() const;
    string write_convolution_type() const;

    Index get_column_stride() const;

    Index get_row_stride() const;

    Index get_kernels_number() const;
    Index get_kernels_channels_number() const;
    Index get_kernels_rows_number() const;
    Index get_kernels_columns_number() const;

    Index get_padding_width() const;
    Index get_padding_height() const;

    Index get_inputs_channels_number() const;
    Index get_inputs_rows_number() const;
    Index get_inputs_columns_number() const;

    Index get_inputs_number() const;
    Index get_neurons_number() const;

    Tensor<type, 1> get_parameters() const;
    Index get_parameters_number() const;

    // Set methods

    void set(const Tensor<Index, 1>&, const Tensor<Index, 1>&);

    void set_name(const string&);

    void set_activation_function(const ActivationFunction&);
    void set_activation_function(const string&);

    void set_biases(const Tensor<type, 1>&);

    void set_synaptic_weights(const Tensor<type, 4>&);

    void set_convolution_type(const ConvolutionType&);
    void set_convolution_type(const string&);

    void set_parameters(const Tensor<type, 1>&, const Index& index = 0);

    void set_row_stride(const Index&);

    void set_column_stride(const Index&);

    void set_inputs_dimenisons(const Tensor<Index,1>&);

    // Initialization

    void set_biases_constant(const type&);

    void set_synaptic_weights_constant(const type&);

    void set_parameters_constant(const type&);

    void set_parameters_random();

    // Padding

    void insert_padding(const Tensor<type, 4>&, Tensor<type, 4>&);

    // Combinations

    void calculate_convolutions(const Tensor<type, 4>&, type*) const; //change

    void calculate_convolutions(const Tensor<type, 4>&,
                                const Tensor<type, 2>&,
                                const Tensor<type, 4>&,
                                Tensor<type, 4>&) const; //change
    // Activation

    void calculate_activations(type*, const Tensor<Index, 1>&,
                               type*, const Tensor<Index, 1>&) const;

    void calculate_activations_derivatives(type*, const Tensor<Index, 1>&,
                                           type*, const Tensor<Index, 1>&,
                                           type*, const Tensor<Index, 1>&) const;

   // Outputs

    void forward_propagate(type*, const Tensor<Index, 1>&, LayerForwardPropagation*, const bool&) final;

   // Outputs

   // Delta methods

   void calculate_hidden_delta(LayerForwardPropagation*,
                               LayerBackPropagation*,
                               LayerBackPropagation*) const final;

   void calculate_hidden_delta(FlattenLayerForwardPropagation*,
                               FlattenLayerBackPropagation*,
                               ConvolutionalLayerBackPropagation*) const;

   // @todo probabilistic hidden delta

   // Gradient methods

   void calculate_error_gradient(type*,
                                 LayerForwardPropagation*,
                                 LayerBackPropagation*) const; //change

   void insert_gradient(LayerBackPropagation*,
                        const Index&,
                        Tensor<type, 1>&) const; // change

   void from_XML(const tinyxml2::XMLDocument&) final;
   void write_XML(tinyxml2::XMLPrinter&) const final;

protected:

   /// This tensor containing conection strengths from a layer's inputs to its neurons.

   Tensor<type, 4> synaptic_weights;

   /// Bias is a neuron parameter that is summed with the neuron's weighted inputs
   /// and passed through the neuron's trabsfer function to generate the neuron's output.

   Tensor<type, 1> biases;

   Index row_stride = 1;

   Index column_stride = 1;

   Tensor<Index, 1> inputs_dimensions;

   ConvolutionType convolution_type = ConvolutionType::Valid;

   ActivationFunction activation_function = ActivationFunction::Linear;

   const Eigen::array<ptrdiff_t, 3> convolution_dimensions = {0, 1, 2};

#ifdef OPENNN_CUDA
    #include "../../opennn-cuda/opennn-cuda/convolutional_layer_cuda.h"
#else
};
#endif


struct ConvolutionalLayerForwardPropagation : LayerForwardPropagation
{
    // Default constructor

    explicit ConvolutionalLayerForwardPropagation()
        : LayerForwardPropagation()
    {
    }

    // Constructor

    explicit ConvolutionalLayerForwardPropagation(const Index& new_batch_samples_number, Layer* new_layer_pointer)
        : LayerForwardPropagation()
    {
        set(new_batch_samples_number, new_layer_pointer);
    }


    void set(const Index& new_batch_samples_number, Layer* new_layer_pointer)
    {
        batch_samples_number = new_batch_samples_number;

        layer_pointer = new_layer_pointer;

        const ConvolutionalLayer* convolutional_layer_pointer = static_cast<ConvolutionalLayer*>(layer_pointer);

        const Index kernels_number = convolutional_layer_pointer->get_kernels_number();
        const Index outputs_rows_number = convolutional_layer_pointer->get_outputs_rows_number();
        const Index outputs_columns_number = convolutional_layer_pointer->get_outputs_columns_number();

        convolutions.resize(batch_samples_number, kernels_number, outputs_rows_number, outputs_columns_number);
        activations_derivatives.resize(batch_samples_number, kernels_number, outputs_rows_number, outputs_columns_number);

        convolutions.setZero();
        activations_derivatives.setZero();

        outputs_dimensions.resize(4);
        outputs_dimensions.setValues({batch_samples_number,
                                      kernels_number,
                                      outputs_rows_number, outputs_columns_number});

        outputs_data = (type*) malloc(static_cast<size_t>(batch_samples_number*kernels_number*outputs_rows_number*outputs_columns_number*sizeof(type)));
    }


    void print() const
    {
        cout << "Convolutional" << endl;

        cout << "Convolutions:" << endl;
//        cout << convolutions << endl;

        cout << "Outputs:" << endl;
        cout << TensorMap<Tensor<type,4>>(outputs_data,
                                          outputs_dimensions(0),
                                          outputs_dimensions(1),
                                          outputs_dimensions(2),
                                          outputs_dimensions(3)) << endl;

        cout << "Outputs dimensions:" << endl;
        cout << outputs_dimensions << endl;

        cout << "Activations derivatives:" << endl;
//        cout << activations_derivatives << endl;
    }

    type* get_convolutions_data()
    {
        return convolutions.data();
    }

    type* get_activations_derivatives_data()
    {
        return activations_derivatives.data();
    }

    Tensor<type, 4> convolutions;
    Tensor<type, 4> activations_derivatives;
};


struct ConvolutionalLayerBackPropagation : LayerBackPropagation
{

    explicit ConvolutionalLayerBackPropagation() : LayerBackPropagation()
    {
    }

    virtual ~ConvolutionalLayerBackPropagation()
    {
    }


    explicit ConvolutionalLayerBackPropagation(const Index& new_batch_samples_number, Layer* new_layer_pointer)
        : LayerBackPropagation()
    {
        set(new_batch_samples_number, new_layer_pointer);
    }


    void set(const Index& new_batch_samples_number, Layer* new_layer_pointer)
    {
        batch_samples_number = new_batch_samples_number;

        layer_pointer = new_layer_pointer;

        const ConvolutionalLayer* convolutional_layer_pointer = static_cast<ConvolutionalLayer*>(layer_pointer);

        const Index kernels_number = convolutional_layer_pointer->get_kernels_number();
        const Index kernels_channels_number = convolutional_layer_pointer->get_kernels_channels_number();
        const Index kernesl_rows_number = convolutional_layer_pointer->get_kernels_rows_number();
        const Index kernels_columns_number = convolutional_layer_pointer->get_kernels_columns_number();

        const Index outputs_rows_number = convolutional_layer_pointer->get_outputs_rows_number();
        const Index outputs_columns_number = convolutional_layer_pointer->get_outputs_columns_number();
        const Index synaptic_weights_number = convolutional_layer_pointer->get_synaptic_weights_number();

        deltas_dimensions.resize(4);

        deltas_dimensions.setValues({batch_samples_number,
                                     kernels_number,
                                     outputs_rows_number,
                                     outputs_columns_number});

        deltas_data = (type*)malloc(static_cast<size_t>(batch_samples_number*kernels_number*outputs_rows_number*outputs_columns_number*sizeof(type)));

        deltas_times_activations_derivatives.resize(batch_samples_number,
                                                    kernels_number,
                                                    outputs_rows_number,
                                                    outputs_columns_number);

        biases_derivatives.resize(kernels_number);

        synaptic_weights_derivatives.resize(kernels_number,
                                            kernels_channels_number,
                                            kernesl_rows_number,
                                            kernels_columns_number);
    }


    void print() const
    {
        cout << "Deltas:" << endl;
        //cout << deltas << endl;

        cout << "Biases derivatives:" << endl;
        cout << biases_derivatives << endl;

        cout << "Synaptic weights derivatives:" << endl;
        cout << synaptic_weights_derivatives << endl;

    }

    Tensor<type, 4> deltas_times_activations_derivatives;

    Tensor<type, 1> biases_derivatives;
    Tensor<type, 4> synaptic_weights_derivatives;
};

#ifdef OPENNN_CUDA
    #include "../../opennn-cuda/opennn-cuda/struct_convolutional_layer_cuda.h"
#endif

}

#endif


// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2023 Artificial Intelligence Techniques, SL.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software

// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
