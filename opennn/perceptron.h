/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   P E R C E P T R O N   C L A S S   H E A D E R                                                              */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __PERCEPTRON_H__
#define __PERCEPTRON_H__

// System includes

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

// OpenNN includes

#include "vector.h"
#include "matrix.h"

namespace OpenNN
{

/// This class represents the concept of perceptron neuron model.
/// A perceptron will be used to construct layers of perceptrons, which will be used to construct multilayer perceptrons. 
/// The perceptron implemented here admits a variety of activation or transfer functions. 

class Perceptron
{
public:

   // DEFAULT CONSTRUCTOR

   explicit Perceptron(void);

   // INPUTS NUMBER CONSTRUCTOR

   explicit Perceptron(const size_t&);

   // INPUTS NUMBER AND INITIALIZATION CONSTRUCTOR

   explicit Perceptron(const size_t&, const double&);

   // COPY CONSTRUCTOR

   Perceptron(const Perceptron&);

   // DESTRUCTOR

   virtual ~Perceptron(void);

   // ASSIGNMENT OPERATOR

   Perceptron& operator = (const Perceptron&);

   // EQUAL TO OPERATOR

   bool operator == (const Perceptron&) const;

   // ENUMERATIONS

   /// Enumeration of available activation functions for the perceptron neuron model. 

   enum ActivationFunction{Threshold, SymmetricThreshold, Logistic, HyperbolicTangent, Linear};

   // METHODS

   // Get methods

   size_t get_inputs_number(void) const;

   const ActivationFunction& get_activation_function(void) const;
   std::string write_activation_function(void) const;

   const double& get_bias(void) const;   
   const Vector<double>& arrange_synaptic_weights(void) const;
   const double& get_synaptic_weight(const size_t&) const;

   size_t count_parameters_number(void) const;
   Vector<double> arrange_parameters(void) const;

   const bool& get_display(void) const;

   // Set methods

   void set(void);
   void set(const size_t&);
   void set(const size_t&, const double&);
   void set(const Perceptron&);

   void set_inputs_number(const size_t&);

   void set_activation_function(const ActivationFunction&);
   void set_activation_function(const std::string&);

   void set_bias(const double&);
   void set_synaptic_weights(const Vector<double>&);
   void set_synaptic_weight(const size_t&, const double&);

   void set_parameters(const Vector<double>&);

   void set_display(const bool&);

   // Growing and pruning

   void grow_input(void);

   void prune_input(const size_t&);

   // Initialization methods

   void initialize_bias(const double&);
   void initialize_bias_uniform(const double&, const double&);
   void initialize_bias_normal(const double&, const double&);

   void initialize_synaptic_weights(const double&);
   void initialize_synaptic_weights_uniform(const double&, const double&);
   void initialize_synaptic_weights_normal(const double&, const double&);

   void initialize_parameters(const double&);

   // Combination methods

   double calculate_combination(const Vector<double>&) const;
   Vector<double> calculate_combination_gradient(const Vector<double>&) const;
   Matrix<double> calculate_combination_Hessian(const Vector<double>&) const;

   double calculate_combination(const Vector<double>&, const Vector<double>&) const;
   Vector<double> calculate_combination_gradient(const Vector<double>&, const Vector<double>&) const;
   Matrix<double> calculate_combination_Hessian(const Vector<double>&, const Vector<double>&) const;

   // Activation methods

   double calculate_activation(const double&) const ;
   double calculate_activation_derivative(const double&) const ;
   double calculate_activation_second_derivative(const double&) const ;

   // Output methods

   double calculate_output(const Vector<double>&) const;
   Vector<double> calculate_gradient(const Vector<double>&) const;
   Matrix<double> calculate_Hessian(const Vector<double>&) const;

   double calculate_output(const Vector<double>&, const Vector<double>&) const;
   Vector<double> calculate_gradient(const Vector<double>&, const Vector<double>&) const;
   Matrix<double> calculate_Hessian(const Vector<double>&, const Vector<double>&) const;

   // Expression methods

   std::string write_expression(const Vector<std::string>&, const std::string&) const;

private: 

   // MEMBERS

   /// Bias value.

   double bias;

   /// Synaptic weights vector.

   Vector<double> synaptic_weights;

   /// Activation function variable. 

   ActivationFunction activation_function;

   /// Display messages to screen. 

   bool display;

};

}

#endif


// OpenNN: Open Neural Networks Library.
// Copyright (c) 2005-2016 Roberto Lopez.
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

