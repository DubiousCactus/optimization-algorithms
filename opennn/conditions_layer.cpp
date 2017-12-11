/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   C O N D I T I O N S   L A Y E R   C L A S S                                                                */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "conditions_layer.h"

namespace OpenNN
{

// DEFAULT CONSTRUCTOR

/// Default constructor. 
/// It creates a conditions layer object.

ConditionsLayer::ConditionsLayer(void)
{
   set();

   set_default();
}


// INPUTS-OUTPUTS NUMBER CONSTRUCTOR

/// Inputs and outputs number constructor.
/// @param new_inputs_number Number of inputs. 
/// @param new_conditions_neurons_number Number of conditions neurons. 

ConditionsLayer::ConditionsLayer(const size_t& new_inputs_number, const size_t& new_conditions_neurons_number)
{
   set(new_inputs_number, new_conditions_neurons_number);

   set_default();
}


// XML CONSTRUCTOR

/// XML constructor. 
/// @param conditions_layer_document Pointer to a TinyXML document with the member data. 

ConditionsLayer::ConditionsLayer(const tinyxml2::XMLDocument& conditions_layer_document)
{
   set_default();

   from_XML(conditions_layer_document);
}


// COPY CONSTRUCTOR

/// Copy constructor.
/// @param other_conditions_layer Conditions layer object to be copied. 

ConditionsLayer::ConditionsLayer(const ConditionsLayer& other_conditions_layer)
{
   set(other_conditions_layer);
}


// DESTRUCTOR

/// Destructor.

ConditionsLayer::~ConditionsLayer(void)
{
}


// ASSIGNMENT OPERATOR

/// Assignment operator. 
/// It assigns to this object the members of an existing conditions layer object.
/// @param other_conditions_layer Conditions layer object to be assigned.

ConditionsLayer& ConditionsLayer::operator = (const ConditionsLayer& other_conditions_layer)
{
   if(this != &other_conditions_layer) 
   {
      external_inputs_number = other_conditions_layer.external_inputs_number;
      conditions_neurons_number = other_conditions_layer.conditions_neurons_number;
      conditions_method = other_conditions_layer.conditions_method;
      external_input_values = other_conditions_layer.external_input_values;
      output_values = other_conditions_layer.output_values;
      display = other_conditions_layer.display;
   }

   return(*this);
}


// EQUAL TO OPERATOR

// bool operator == (const ConditionsLayer&) const method

/// Equal to operator. 
/// It compares this object with another object of the same class. 
/// It returns true if the members of the two objects have the same values, and false otherwise.
/// @ param other_conditions_layer Conditions layer to be compared with.

bool ConditionsLayer::operator == (const ConditionsLayer& other_conditions_layer) const
{
    if(external_inputs_number == other_conditions_layer.external_inputs_number
    && conditions_neurons_number == other_conditions_layer.conditions_neurons_number
    && conditions_method == other_conditions_layer.conditions_method
    && external_input_values == other_conditions_layer.external_input_values
    && output_values == other_conditions_layer.output_values
    && display == other_conditions_layer.display)
    {
       return(true);
    }
    else
    {
       return(false);
    }
}


// METHODS

// const size_t& get_external_inputs_number(void) const method

/// Returns the number of external inputs. 

const size_t& ConditionsLayer::get_external_inputs_number(void) const
{
   return(external_inputs_number);
}


// const size_t& get_conditions_neurons_number(void) const method

/// Returns the number of conditions neurons. 

const size_t& ConditionsLayer::get_conditions_neurons_number(void) const
{
   return(conditions_neurons_number);
}


// const ConditionsMethod& get_conditions_method(void) const method

/// Returns the method for calculating the conditions.
/// Avaliable methods include one conditions, two conditions or user defined conditions.

const ConditionsLayer::ConditionsMethod& ConditionsLayer::get_conditions_method(void) const
{
   return(conditions_method);
}


// std::string write_conditions_method(void) const method

/// Returns a string with the name of the method for calculating the conditions.
/// Avaliable methods include one conditions, two conditions or user defined conditions.

std::string ConditionsLayer::write_conditions_method(void) const
{
   if(conditions_method == OneCondition)
   {
      return("OneCondition");
   }
   else if(conditions_method == TwoConditions)
   {
      return("TwoConditions");
   }
   else
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: ConditionsLayer class.\n"
             << "std::string write_conditions_method(void) const method.\n"
             << "Unknown conditions method.\n";
 
	  throw std::logic_error(buffer.str());
   }
}


// const Vector<double>& get_external_input_values(void) const method

/// Returns the input values for the conditions. 

const Vector<double>& ConditionsLayer::get_external_input_values(void) const
{
   return(external_input_values);
}


// const double& get_external_input_value(const size_t&) const method

/// Returns a single input value for the conditions. 
/// @param i Index of condition. 

const double& ConditionsLayer::get_external_input_value(const size_t& i) const
{
   return(external_input_values[i]);
}   


// const Matrix<double>& get_output_values(void) const method

/// Returns the output values for the conditions. 

const Matrix<double>& ConditionsLayer::get_output_values(void) const
{
   return(output_values);
}


// const double& get_exteoutput_value(const size_t&, const size_t&) const method

/// Returns a single output value for the conditions. 
/// @param i Index of output. 
/// @param j Index of condition. 

const double& ConditionsLayer::get_output_value(const size_t& i, const size_t& j) const
{
   return(output_values(i,j));
}


// const bool& get_display(void) const method

/// Returns true if messages from this class are to be displayed on the screen, or false if messages 
/// from this class are not to be displayed on the screen.

const bool& ConditionsLayer::get_display(void) const
{
   return(display);
}


// void set(void) method

/// Sets a conditions layer object with zero inputs and zero outputs.
/// It also sets the rest of members to their default values. 

void ConditionsLayer::set(void)
{
   external_inputs_number = 0;

   conditions_neurons_number = 0;

   set_default();
}


// void set(const size_t&, const size_t&) method

/// Sets the numbers of external inputs and conditions neurons. 
/// It also sets the rest of members to their default values. 

void ConditionsLayer::set(const size_t& new_external_inputs_number, const size_t& new_conditions_neurons_number)
{
   external_inputs_number = new_external_inputs_number;

   conditions_neurons_number = new_conditions_neurons_number;

   set_default();
}


// void set(const ConditionsLayer&) method

/// Sets the members of this conditions layer object with those from other conditions layer object. 
/// @param other_conditions_layer Conditions layer object to be copied. 

void ConditionsLayer::set(const ConditionsLayer& other_conditions_layer)
{
   external_inputs_number = other_conditions_layer.external_inputs_number;

   conditions_neurons_number = other_conditions_layer.conditions_neurons_number;

   conditions_method = other_conditions_layer.conditions_method;

   external_input_values = other_conditions_layer.external_input_values;
   output_values = other_conditions_layer.output_values;

   display = other_conditions_layer.display;
}


// void set_default(void) method

/// Sets the members of this conditions layer object to their default values. 

void ConditionsLayer::set_default(void)
{
   conditions_method = TwoConditions;

   if(conditions_neurons_number == 0)
   {
      external_input_values.set();

      output_values.set();
   }
   else
   {
      external_input_values.set(2, 0.0);

      output_values.set(conditions_neurons_number, 2, 0.0);
   }

   display = true;
}


// void set_external_inputs_number(const size_t&) method

/// Sets the number of external inputs in the conditions layer. 
/// @param new_external_inputs_number Number of external inputs. 

void ConditionsLayer::set_external_inputs_number(const size_t& new_external_inputs_number)
{
   external_inputs_number = new_external_inputs_number;
}


// void set_conditions_neurons_number(const size_t&) method

/// Sets the number of conditions neurons in the layer. 
/// @param new_conditions_neurons_number Number of conditions neurons. 

void ConditionsLayer::set_conditions_neurons_number(const size_t& new_conditions_neurons_number)
{
   conditions_neurons_number = new_conditions_neurons_number;
}


// void set_conditions_method(const ConditionsMethod&) method

/// Sets a new method for calculating the conditions. 
/// @param new_conditions_method Conditions method. 

void ConditionsLayer::set_conditions_method(const ConditionsMethod& new_conditions_method)
{
	conditions_method = new_conditions_method;
}


// void set_conditions_method(const std::string&) method

/// Sets a new conditions method from the string. 
/// @param new_conditions_method String with the name of the conditions method. 

void ConditionsLayer::set_conditions_method(const std::string& new_conditions_method)
{
   if(new_conditions_method == "OneCondition")
   {
      set_conditions_method(OneCondition);
   }
   else if(new_conditions_method == "TwoConditions")
   {
      set_conditions_method(TwoConditions);
   }
   else if(new_conditions_method == "UserConditionsMethod")
   {
      set_conditions_method(UserConditionsMethod);
   }
   else
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: ConditionsLayer class.\n"
             << "void set_conditions_method(const std::string&) method.\n"
			 << "Unknown conditions method: " << new_conditions_method << ".\n";

	  throw std::logic_error(buffer.str());
   }
}


// void set_external_input_values(const Vector<double>&) method

/// Sets a new vector of external input values. 
/// @param new_external_input_values External input values. 

void ConditionsLayer::set_external_input_values(const Vector<double>& new_external_input_values)
{
   external_input_values = new_external_input_values;
}


// void set_external_input_value(const size_t&, const double&) method

/// Sets a single external input value. 
/// @param i Index of external input value. 
/// @param new_external_input_value External input value. 

void ConditionsLayer::set_external_input_value(const size_t& i, const double& new_external_input_value)
{
   external_input_values[i] = new_external_input_value;
}


// void set_output_values(const Matrix<double>&) method

/// Sets a new matrix of output values. 
/// @param new_output_values Output values. 

void ConditionsLayer::set_output_values(const Matrix<double>& new_output_values)
{
   output_values = new_output_values;
}


// void set_output_value(const size_t&, const double&) method

/// Sets a single output value. 
/// @param i Index of row. 
/// @param j Index of column. 
/// @param new_output_value Output value. 

void ConditionsLayer::set_output_value(const size_t& i, const size_t& j, const double& new_output_value)
{
   output_values(i,j) = new_output_value;
}


// void set_display(const bool&) method

/// Sets a new display value. 
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.

void ConditionsLayer::set_display(const bool& new_display)
{
   display = new_display;
}


// void initialize_random(void) method

/// @todo

void ConditionsLayer::initialize_random(void)
{

}


// void check(void) const method

/// Checks that all the members of the conditions layer are correct before calculating the outputs from that layer.

void ConditionsLayer::check(void) const
{
   std::ostringstream buffer;

   if(conditions_method == OneCondition || conditions_method == TwoConditions)
   {
      if(external_inputs_number != 1)
      {
         buffer << "OpenNN Exception: BoundingLayer class.\n" 
                << "void check(void) const method.\n"
                << "Number of external inputs must be one.\n";

	     throw std::logic_error(buffer.str());
      }
   }

   const size_t external_input_values_size = external_input_values.size();

   const size_t output_values_rows_number = output_values.get_rows_number();
   const size_t output_values_columns_number = output_values.get_rows_number();

   if(output_values_rows_number != conditions_neurons_number)
   {
      buffer << "OpenNN Exception: BoundingLayer class.\n" 
             << "void check(void) const method.\n"
             << "Number of rows in output values is not equal to number of conditions neurons.\n";

      throw std::logic_error(buffer.str());
   }

   if(conditions_method == OneCondition)
   {
      if(external_input_values_size != 1)
	  {	  
         buffer << "OpenNN Exception: BoundingLayer class.\n" 
                << "void check(void) const method.\n"
                << "Size of input values is not 1.\n";

         throw std::logic_error(buffer.str());
	  }

	  if(output_values_columns_number != 1)
	  {
         buffer << "OpenNN Exception: BoundingLayer class.\n" 
                << "void check(void) const method.\n"
                << "Number of columns in output values is not 1.\n";

         throw std::logic_error(buffer.str());
	  }
   }
   else if(conditions_method == OneCondition)
   {
      if(external_input_values_size != 2)
	  {	  
         buffer << "OpenNN Exception: BoundingLayer class.\n" 
                << "void check(void) const method.\n"
                << "Size of input values is not 2.\n";

         throw std::logic_error(buffer.str());
	  }

	  if(output_values_columns_number != 2)
	  {
         buffer << "OpenNN Exception: BoundingLayer class.\n" 
                << "void check(void) const method.\n"
                << "Number of columns in output values is not 2.\n";

         throw std::logic_error(buffer.str());
	  }
   }
}


// Vector<double> calculate_particular_solution(const Vector<double>&) const method

/// Returns the particular solution function for applying conditions.
/// @param external_inputs Vector of external inputs.

Vector<double> ConditionsLayer::calculate_particular_solution(const Vector<double>& external_inputs) const
{
   switch(conditions_method)
   {
      case OneCondition:
      {
         return(calculate_one_condition_particular_solution(external_inputs));
      }            
      break;

      case TwoConditions:
      {
         return(calculate_two_conditions_particular_solution(external_inputs));
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: ScalingLayer class\n"
                << "Vector<double> calculate_particular_solution(const Vector<double>&) const method.\n"               
                << "Unknown conditions method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }
}


// Matrix<double> calculate_particular_solution_Jacobian(const Vector<double>&) const method

/// Returns the particular solution Jacobian for applying conditions.
/// @param external_inputs Vector of external inputs.

Matrix<double> ConditionsLayer::calculate_particular_solution_Jacobian(const Vector<double>& external_inputs) const
{
   switch(conditions_method)
   {
      case OneCondition:
      {
         return(calculate_one_condition_particular_solution_Jacobian(external_inputs));
      }            
      break;

      case TwoConditions:
      {
         return(calculate_two_conditions_particular_solution_Jacobian(external_inputs));
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: ScalingLayer class\n"
                << "Matrix<double> calculate_particular_solution_Jacobian(const Vector<double>&) const method.\n"               
                << "Unknown conditions method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }
}


// Vector< Matrix<double> >  calculate_particular_solution_Hessian_form(const Vector<double>&) const method

/// Returns the Hessian form of the particular solution. 
/// @param external_inputs Vector of external inputs.

Vector< Matrix<double> >  ConditionsLayer::calculate_particular_solution_Hessian_form(const Vector<double>& external_inputs) const
{
   switch(conditions_method)
   {
      case OneCondition:
      {
         return(calculate_one_condition_particular_solution_Hessian_form(external_inputs));
      }            
      break;

      case TwoConditions:
      {
         return(calculate_two_conditions_particular_solution_Hessian_form(external_inputs));
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: ScalingLayer class\n"
                << "Vector< Matrix<double> > calculate_particular_solution_Hessian_form(const Vector<double>&) const method.\n"               
                << "Unknown conditions method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }
}


// Vector<double> calculate_homogeneous_solution(const Vector<double>&) const method

/// Returns the homogeneous solution values for applying conditions.
/// @param external_inputs Vector of external inputs.

Vector<double> ConditionsLayer::calculate_homogeneous_solution(const Vector<double>& external_inputs) const
{
   switch(conditions_method)
   {
      case OneCondition:
      {
         return(calculate_one_condition_homogeneous_solution(external_inputs));
      }            
      break;

      case TwoConditions:
      {
         return(calculate_two_conditions_homogeneous_solution(external_inputs));
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: ScalingLayer class\n"
                << "Vector<double> calculate_homogeneous_solution(const Vector<double>&) const method.\n"               
                << "Unknown conditions method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }
}


// Matrix<double> calculate_homogeneous_solution_Jacobian(const Vector<double>&) const method

/// Returns the homogeneous solution Jacobian for applying conditions.
/// @param external_inputs Vector of external inputs.

Matrix<double> ConditionsLayer::calculate_homogeneous_solution_Jacobian(const Vector<double>& external_inputs) const
{
   switch(conditions_method)
   {
      case OneCondition:
      {
         return(calculate_one_condition_homogeneous_solution_Jacobian(external_inputs));
      }            
      break;

      case TwoConditions:
      {
         return(calculate_two_conditions_homogeneous_solution_Jacobian(external_inputs));
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: ScalingLayer class\n"
                << "Matrix<double> calculate_homogeneous_solution_Jacobian(const Vector<double>&) const method.\n"               
                << "Unknown conditions method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }
}


// Vector< Matrix<double> > calculate_homogeneous_solution_Hessian_form(const Vector<double>&) const method

/// Returns the Hessian form of the homogeneous solution function. 
/// @param external_inputs Vector of external inputs.

Vector< Matrix<double> > ConditionsLayer::calculate_homogeneous_solution_Hessian_form(const Vector<double>& external_inputs) const
{
   switch(conditions_method)
   {
      case OneCondition:
      {
         return(calculate_one_condition_homogeneous_solution_Hessian_form(external_inputs));
      }            
      break;

      case TwoConditions:
      {
         return(calculate_two_conditions_homogeneous_solution_Hessian_form(external_inputs));
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: ScalingLayer class\n"
                << "Matrix<double> calculate_homogeneous_solution_Hessian_form(const Vector<double>&) const method.\n"               
                << "Unknown conditions method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }
}


// Vector<double> calculate_outputs(const Vector<double>&, const Vector<double>&) const method

/// Returns the outputs satisfying the conditions defined by the particular and homogeneous solutions. 
/// @param external_inputs Vector of external inputs.
/// @param inputs Vector of inputs to the conditons layer. 

Vector<double> ConditionsLayer::calculate_outputs(const Vector<double>& external_inputs, const Vector<double>& inputs) const
{
   const Vector<double> particular_solution = calculate_particular_solution(external_inputs);
   const Vector<double> homogeneous_solution = calculate_homogeneous_solution(external_inputs);

   return(particular_solution + homogeneous_solution*inputs);
}


// Matrix<double> calculate_Jacobian(const Vector<double>&, const Vector<double>&) const method

/// Calculates the partial derivatives of the outputs satisfying some boundary conditions with respect to the raw outputs. 
/// @param external_inputs Vector of external inputs.
/// @param outputs Vector of outputs from the conditions layer.
/// @param Jacobian Partial derivatives of the raw outputs with respect to the inputs. 

Matrix<double> ConditionsLayer::calculate_Jacobian(const Vector<double>& external_inputs, const Vector<double>& outputs, const Matrix<double>& Jacobian) const
{
   const Vector<double> homogeneous_solution = calculate_homogeneous_solution(external_inputs);

   const Matrix<double> particular_solution_Jacobian = calculate_particular_solution_Jacobian(external_inputs);
   const Matrix<double> homogeneous_solution_Jacobian = calculate_homogeneous_solution_Jacobian(external_inputs);

   return(particular_solution_Jacobian + homogeneous_solution_Jacobian*outputs + homogeneous_solution*Jacobian);           
}


// Vector< Matrix<double> > calculate_Hessian_form(const Vector<double>&, const Vector<double>&) const method

/// @todo

Vector< Matrix<double> > ConditionsLayer::calculate_Hessian_form(const Vector<double>&, const Vector<double>&) const
{
   Vector< Matrix<double> > Hessian_form(conditions_neurons_number);

   return(Hessian_form);
}


// Vector<double> calculate_one_condition_particular_solution(const Vector<double>&) const method

/// Computes the particular solution for the one boundary condition case.
/// @param external_inputs Vector of external inputs.

Vector<double> ConditionsLayer::calculate_one_condition_particular_solution(const Vector<double>& external_inputs) const
{
   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   const Vector<double> particular_solution(conditions_neurons_number, external_inputs[0]);

   return(particular_solution);
}


// Matrix<double> calculate_one_condition_particular_solution_Jacobian(const Vector<double>&) const method

/// Computes the Jacobian of the particular solution function for the one boundary condition case.

Matrix<double> ConditionsLayer::calculate_one_condition_particular_solution_Jacobian(const Vector<double>&) const
{
   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   const Matrix<double> particular_solution_Jacobian(conditions_neurons_number, 1, 0.0);

   return(particular_solution_Jacobian);
}


// Vector< Matrix<double> > calculate_one_condition_particular_solution_Hessian_form(const Vector<double>&) const method

/// Computes the Hessian form of the particular solution function for the one boundary condition case.
/// @todo

Vector< Matrix<double> > ConditionsLayer::calculate_one_condition_particular_solution_Hessian_form(const Vector<double>&) const
{
   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   Vector< Matrix<double> > particular_solution_Hessian_form(conditions_neurons_number);

   return(particular_solution_Hessian_form);
}


// Vector<double> calculate_one_condition_homogeneous_solution(const Vector<double>&) const method

/// Computes the homogeneous solution for the one boundary condition case.
/// @param external_inputs Vector of external inputs.

Vector<double> ConditionsLayer::calculate_one_condition_homogeneous_solution(const Vector<double>& external_inputs) const
{
   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   const Vector<double> homogeneous_solution(conditions_neurons_number, external_inputs[0]-external_input_values[0]);

   return(homogeneous_solution);
}



// Matrix<double> calculate_one_condition_homogeneous_solution_Jacobian(const Vector<double>&) const method

/// Computes the homogeneous solution Jacobian for the one boundary condition case.

Matrix<double> ConditionsLayer::calculate_one_condition_homogeneous_solution_Jacobian(const Vector<double>&) const
{
   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   const Matrix<double> homogeneous_solution_Jacobian(conditions_neurons_number, 1, 1.0);

   return(homogeneous_solution_Jacobian);
}


// Vector< Matrix<double> > calculate_one_condition_homogeneous_solution_Hessian_form(const Vector<double>&) const method

/// Computes the homogeneous solution Hessian form for the one boundary condition case.
/// @todo

Vector< Matrix<double> > ConditionsLayer::calculate_one_condition_homogeneous_solution_Hessian_form(const Vector<double>&) const
{
   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   Vector< Matrix<double> > homogeneous_solution_Hessian_form(conditions_neurons_number);

   return(homogeneous_solution_Hessian_form);
}


// Vector<double> calculate_two_conditions_particular_solution(const Vector<double>&) const method

/// Computes the particular solution for the two boundary conditions case.
/// @param external_inputs Vector of external inputs.

Vector<double> ConditionsLayer::calculate_two_conditions_particular_solution(const Vector<double>& external_inputs) const
{
   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   const double x = external_inputs[0];

   const double xa = external_input_values[0];
   const double xb = external_input_values[1];

   #ifdef __OPENNN_DEBUG__ 

   if(xb - xa < 1.0e-99)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: BoundingLayer class.\n" 
             << "Vector<double> calculate_two_conditions_particular_solution(const Vector<double>&) const method.\n"
             << "Both input values are the same.\n";

	  throw std::logic_error(buffer.str());   
   }

   #endif

   double ya;
   double yb;

   Vector<double> particular_solutions(conditions_neurons_number);

   for(size_t i = 0; i < conditions_neurons_number; i++)
   {
      ya = output_values(i,0);
      yb = output_values(i,1);

      particular_solutions[i] = ya + (yb-ya)*(x-xa)/(double)(xb-xa);
   }

   return(particular_solutions);
}


// Vector<double> calculate_two_conditions_particular_solution_Jacobian(const Vector<double>&) const method

/// Computes the particular solution Jacobian for the two boundary conditions case.
/// @todo

Matrix<double> ConditionsLayer::calculate_two_conditions_particular_solution_Jacobian(const Vector<double>&) const
{
   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   const double xa = external_input_values[0];
   const double xb = external_input_values[1];

   #ifdef __OPENNN_DEBUG__ 

   if(xb - xa < 1.0e-99)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: BoundingLayer class.\n" 
             << "Matrix<double> calculate_two_conditions_particular_solution_Jacobian(const Vector<double>&) const method.\n"
             << "Both input values are the same.\n";

	  throw std::logic_error(buffer.str());   
   }

   #endif

   const double ya = output_values(0,0);
   const double yb = output_values(0,1);

   Matrix<double> particular_solution_Jacobian(1, 1, (yb-ya)/(xb-xa));

   return(particular_solution_Jacobian);
}


// Vector<double> calculate_two_conditions_particular_solution_Hessian_form(const Vector<double>&) const method

/// Computes the particular solution Hessian form for the two boundary conditions case.
/// @todo

Vector< Matrix<double> > ConditionsLayer::calculate_two_conditions_particular_solution_Hessian_form(const Vector<double>&) const
{
   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   Vector< Matrix<double> > particular_solution_Hessian_form(conditions_neurons_number);

   return(particular_solution_Hessian_form);
}


// Vector<double> calculate_two_conditions_homogeneous_solution(const Vector<double>&) const method

/// Computes the homogeneous solution for the two boundary conditions case.
/// @param external_inputs Vector of external inputs.

Vector<double> ConditionsLayer::calculate_two_conditions_homogeneous_solution(const Vector<double>& external_inputs) const
{
   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   const double x = external_inputs[0];

   const double xa = external_input_values[0];
   const double xb = external_input_values[1];

   #ifdef __OPENNN_DEBUG__ 

   if(xb - xa < 1.0e-99)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: BoundingLayer class.\n" 
             << "Matrix<double> calculate_two_conditions_particular_solution_Jacobian(const Vector<double>&) const method.\n"
             << "Both input values are the same.\n";

	  throw std::logic_error(buffer.str());   
   }

   #endif

   const Vector<double> homogeneous_solutions(conditions_neurons_number, (x-xa)*(x-xb));

   return(homogeneous_solutions);
}


// Matrix<double> calculate_two_conditions_homogeneous_solution_Jacobian(const Vector<double>&) const method

/// Computes the homogeneous solution Jacobian for the two boundary conditions case.
/// @param external_inputs Vector of external inputs.

Matrix<double> ConditionsLayer::calculate_two_conditions_homogeneous_solution_Jacobian(const Vector<double>& external_inputs) const
{
   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   const double x = external_inputs[0];

   const double xa = external_input_values[0];
   const double xb = external_input_values[1];

   #ifdef __OPENNN_DEBUG__ 

   if(xb - xa < 1.0e-99)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: BoundingLayer class.\n" 
             << "Matrix<double> calculate_two_conditions_particular_solution_Jacobian(const Vector<double>&) const method.\n"
             << "Both input values are the same.\n";

	  throw std::logic_error(buffer.str());   
   }

   #endif

   Matrix<double> homogeneous_solution_Jacobian(1, 1, (x-xa) + (x-xb));

   return(homogeneous_solution_Jacobian);
}


// Vector< Matrix<double> > calculate_two_conditions_homogeneous_solution_Hessian_form(const Vector<double>&) const method

/// Computes the homogeneous solution Hessian form for the two boundary conditions case.
// @todo

Vector< Matrix<double> > ConditionsLayer::calculate_two_conditions_homogeneous_solution_Hessian_form(const Vector<double>&) const
{
   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   Vector< Matrix<double> > homogeneous_solution_Hessian_form(conditions_neurons_number);

   return(homogeneous_solution_Hessian_form);
}


// std::string write_expression(const Vector<std::string>&, const Vector<std::string>&, const Vector<std::string>&) const method

/// Returns a string with the expression of the boundary conditions function. 
/// @param external_inputs_names Names of external inputs. 
/// @param inputs_names Names of inputs. 
/// @param outputs_names Names of outputs. 
/// @todo

std::string ConditionsLayer::write_expression(const Vector<std::string>& external_inputs_names, const Vector<std::string>& inputs_names, const Vector<std::string>& outputs_names) const
{
   std::ostringstream buffer;

   Vector<std::string> particular_solutions_names(conditions_neurons_number);
   Vector<std::string> homogeneous_solutions_names(conditions_neurons_number);

   for(size_t i = 0; i < conditions_neurons_number; i++)
   {
	  buffer.str("");
      buffer << "particular_solution_" << inputs_names[i];       
      particular_solutions_names[i] = buffer.str();

	  buffer.str("");
      buffer << "homogeneous_solution_" << inputs_names[i];       
      homogeneous_solutions_names[i] = buffer.str();
   
	  buffer.str("");
   }      

    buffer << write_particular_solution_expression(external_inputs_names, particular_solutions_names) 
           << write_homogeneous_solution_expression(external_inputs_names, particular_solutions_names);


    for(size_t i = 0; i < conditions_neurons_number; i++)
	{
	   buffer << outputs_names[i] << "=\n"; 
	}
//           << 
//	(external_inputs_names, particular_solutions_names, particular_solutions_names, inputs_names) << "\n";

//   for(size_t i = 0; i < conditions_neurons_number; i++)
//   {
//	   buffer << particular_solutions_names[i] << " = " << write_particular_solution_expression(inputs_names, particular_solutions_names) << "\n"
//              << homogeneous_solutions_names[i] << " = " << "\n";


//      buffer << outputs_names[i] << " = " << particular_solution_expression[i] << "+" << homogeneous_solution_expression[i] << "*" << outputs_expression[i] << ";\n";   
//   }

   return(buffer.str());
}


// std::string write_particular_solution_expression(const Vector<std::string>&, const Vector<std::string>&) const method

/// Returns the expression of the particular solution function. 
/// @param external_inputs_names Names of external inputs. 
/// @param particular_solutions_names Names of particular solutions. 
/// @todo

std::string ConditionsLayer::write_particular_solution_expression(const Vector<std::string>& external_inputs_names, const Vector<std::string>& particular_solutions_names) const
{
   switch(conditions_method)
   {
      case OneCondition:
      {
         return(write_one_condition_particular_solution_expression(external_inputs_names, particular_solutions_names));
      }            
      break;

      case TwoConditions:
      {
         return(write_two_conditions_particular_solution_expression(external_inputs_names, particular_solutions_names));
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: ScalingLayer class\n"
                << "std::string write_particular_solution_expression(const Vector<std::string>&, const Vector<std::string>&) const method.\n"               
                << "Unknown conditions method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }
}


// std::string write_homogeneous_solution_expression(const Vector<std::string>&, const Vector<std::string>&) const method

/// Returns the expression of the homogeneous solution function. 
/// @param external_inputs_names Names of external inputs. 
/// @param homogeneous_solutions_names Names of homogeneous solutions. 
/// @todo

std::string ConditionsLayer::write_homogeneous_solution_expression(const Vector<std::string>& external_inputs_names, const Vector<std::string>& homogeneous_solutions_names) const
{
   switch(conditions_method)
   {
      case OneCondition:
      {
         return(write_one_condition_homogeneous_solution_expression(external_inputs_names, homogeneous_solutions_names));
      }            
      break;

      case TwoConditions:
      {
         return(write_two_conditions_homogeneous_solution_expression(external_inputs_names, homogeneous_solutions_names));
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: ScalingLayer class\n"
                << "std::string write_homogeneous_solution_expression(const Vector<std::string>&, const Vector<std::string>&) const method.\n"
                << "Unknown conditions method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }
}


// std::string write_one_condition_particular_solution_expression(const Vector<std::string>&, const Vector<std::string>&) const method

/// @param external_inputs_names Names of external inputs. 
/// @param particular_solutions_names Names of particular solutions. 
/// @todo

std::string ConditionsLayer::write_one_condition_particular_solution_expression(const Vector<std::string>& external_inputs_names, const Vector<std::string>& particular_solutions_names) const
{
   std::ostringstream buffer;

   for(size_t i = 0; i < conditions_neurons_number; i++)
   {
      buffer << particular_solutions_names[i] << " = " << external_inputs_names[i] << "\n";    
   }

   return(buffer.str());
}


// std::string write_one_condition_homogeneous_solution_expression(const Vector<std::string>&, const Vector<std::string>&) const method

/// @param external_inputs_names Names of external inputs. 
/// @param homogeneous_solutions_names Names of homogeneous solutions. 
/// @todo

std::string ConditionsLayer::write_one_condition_homogeneous_solution_expression(const Vector<std::string>& external_inputs_names, const Vector<std::string>& homogeneous_solutions_names) const
{
   std::ostringstream buffer;

   for(size_t i = 0; i < conditions_neurons_number; i++)
   {
      buffer << homogeneous_solutions_names[i] << " = " << external_inputs_names[i] << "\n";    
   }

   return(buffer.str());
}
   

// std::string write_two_conditions_particular_solution_expression(const Vector<std::string>&, const Vector<std::string>&) const method

/// @param external_inputs_names Names of external inputs. 
/// @param particular_solutions_names Names of particular solutions. 
/// @todo

std::string ConditionsLayer::write_two_conditions_particular_solution_expression(const Vector<std::string>& external_inputs_names, const Vector<std::string>& particular_solutions_names) const
{
   std::ostringstream buffer;

   for(size_t i = 0; i < conditions_neurons_number; i++)
   {
      buffer << particular_solutions_names[i] << " = " << external_inputs_names[i] << "\n";    
   }

   return(buffer.str());
}


// std::string write_two_conditions_homogeneous_solution_expression(const Vector<std::string>&, const Vector<std::string>&) const method

/// @param external_inputs_names Names of external inputs. 
/// @param homogeneous_solutions_names Names of homogeneous solutions. 
/// @todo

std::string ConditionsLayer::write_two_conditions_homogeneous_solution_expression(const Vector<std::string>& external_inputs_names, const Vector<std::string>& homogeneous_solutions_names) const
{
   std::ostringstream buffer;

   for(size_t i = 0; i < conditions_neurons_number; i++)
   {
      buffer << homogeneous_solutions_names[i] << " = " << external_inputs_names[i] << "\n";    
   }

   return(buffer.str());
}


// std::string write_output_expression(const Vector<std::string>&, const Vector<std::string>&, const Vector<std::string>&, const Vector<std::string>&) const method

/// Returns the mathematical expression of the function represented by the conditions layer. 
/// @param particular_solutions_names Names of particular solutions. 
/// @param homogeneous_solutions_names Names of homogeneous solutions. 
/// @param inputs_names Names of inputs. 
/// @param outputs_names Names of outputs. 

std::string ConditionsLayer::write_output_expression(const Vector<std::string>& particular_solutions_names, const Vector<std::string>& homogeneous_solutions_names, const Vector<std::string>& inputs_names, const Vector<std::string>& outputs_names) const
{
   std::ostringstream buffer;

   for(size_t i = 0; i < conditions_neurons_number; i++)
   {
      buffer << outputs_names[i] << "=" << particular_solutions_names[i] << "+" << homogeneous_solutions_names[i] << "*" << inputs_names[i] << ";\n";
   }

   return(buffer.str());
}


// std::string to_string(void) const method

/// Returns a string representation of the current conditions layer object. 

std::string ConditionsLayer::to_string(void) const
{
   std::ostringstream buffer;

   buffer << "Conditions layer\n"
          << "External inputs number: " << external_inputs_number << "\n"
          << "Conditions neurons number: " <<conditions_neurons_number << "\n"
          << "Conditions method: " << write_conditions_method() << "\n"
          << "Input values: " <<external_input_values << "\n"
          << "Output values: " << output_values 
          << "Display: " << display << "\n";

   return(buffer.str());
}


// tinyxml2::XMLDocument* to_XML(void) const method

/// Serializes the conditions layer object into a document of the TinyXML library.

tinyxml2::XMLDocument* ConditionsLayer::to_XML(void) const
{
   tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;

   std::ostringstream buffer;

   tinyxml2::XMLElement* conditions_layer_element = document->NewElement("ConditionsLayer");

   document->InsertFirstChild(conditions_layer_element);

   // Inputs number
   {
      tinyxml2::XMLElement* element = document->NewElement("ExternalInputsNumber");
      conditions_layer_element->LinkEndChild(element);

      buffer.str("");
      buffer << external_inputs_number;

      tinyxml2::XMLText* text = document->NewText(buffer.str().c_str());
      element->LinkEndChild(text);
   }

   // Conditions neurons number 
   {
      tinyxml2::XMLElement* element = document->NewElement("ConditionsNeuronsNumber");
      conditions_layer_element->LinkEndChild(element);

      buffer.str("");
      buffer << conditions_neurons_number;

      tinyxml2::XMLText* text = document->NewText(buffer.str().c_str());
      element->LinkEndChild(text);
   }

   // Conditions method
   {
      tinyxml2::XMLElement* element = document->NewElement("ConditionsMethod");
      conditions_layer_element->LinkEndChild(element);

      buffer.str("");
      buffer << write_conditions_method();

      tinyxml2::XMLText* text = document->NewText(buffer.str().c_str());
      element->LinkEndChild(text);
   }

   // Input values
   {
      tinyxml2::XMLElement* element = document->NewElement("InputValues");
      conditions_layer_element->LinkEndChild(element);

      buffer.str("");
      buffer << external_input_values;

      tinyxml2::XMLText* text = document->NewText(buffer.str().c_str());
      element->LinkEndChild(text);
   }

   // Output values
   {
      tinyxml2::XMLElement* element = document->NewElement("OutputValues");
      conditions_layer_element->LinkEndChild(element);

      buffer.str("");
      buffer << output_values.to_vector();

      tinyxml2::XMLText* text = document->NewText(buffer.str().c_str());
      element->LinkEndChild(text);
   }

   // Display
   {
      tinyxml2::XMLElement* display_element = document->NewElement("Display");
      conditions_layer_element->LinkEndChild(display_element);

      buffer.str("");
      buffer << display;

      tinyxml2::XMLText* display_text = document->NewText(buffer.str().c_str());
      display_element->LinkEndChild(display_text);
   }

   return(document);
}


// void write_XML(tinyxml2::XMLPrinter&) const method

/// Serializes the conditions layer object into a document of the TinyXML library without keep the DOM tree in memory.

void ConditionsLayer::write_XML(tinyxml2::XMLPrinter& file_stream) const
{
    std::ostringstream buffer;

    file_stream.OpenElement("ConditionsLayer");

    // Inputs number

    {
        file_stream.OpenElement("ExternalInputsNumber");

        buffer.str("");
        buffer << external_inputs_number;

        file_stream.PushText(buffer.str().c_str());

        file_stream.CloseElement();
    }

    // Conditions neurons number

    {
        file_stream.OpenElement("ConditionsNeuronsNumber");

        buffer.str("");
        buffer << conditions_neurons_number;

        file_stream.PushText(buffer.str().c_str());

        file_stream.CloseElement();
    }

    // Conditions method

    {
        file_stream.OpenElement("ConditionsMethod");

        buffer.str("");
        buffer << write_conditions_method();

        file_stream.PushText(buffer.str().c_str());

        file_stream.CloseElement();
    }

    // Input values

    {
        file_stream.OpenElement("InputValues");

        buffer.str("");
        buffer << external_input_values;

        file_stream.PushText(buffer.str().c_str());

        file_stream.CloseElement();
    }

    // Output values

    {
        file_stream.OpenElement("OutputValues");

        buffer.str("");
        buffer << output_values.to_vector();

        file_stream.PushText(buffer.str().c_str());

        file_stream.CloseElement();
    }

    // Display

    {
        file_stream.OpenElement("Display");

        buffer.str("");
        buffer << display;

        file_stream.PushText(buffer.str().c_str());

        file_stream.CloseElement();
    }

    file_stream.CloseElement();
}

// void from_XML(const tinyxml2::XMLDocument&) method

/// Deserializes a TinyXML document into this conditions layer object.
/// @param document TinyXML document containing the member data.
/// @todo

void ConditionsLayer::from_XML(const tinyxml2::XMLDocument& document)
{
  // Inputs number
  {
     const tinyxml2::XMLElement* element = document.FirstChildElement("ExternalInputsNumber");

     if(element)
     {
        const char* text = element->GetText();

        if(text)
        {
           try
           {
              set_external_inputs_number(atoi(text));
           }
           catch(const std::logic_error& e)
           {
              std::cout << e.what() << std::endl;
           }
        }
     }
  }

  // Inputs number
  {
     const tinyxml2::XMLElement* element = document.FirstChildElement("ConditionsNeuronsNumber");

     if(element)
     {
        const char* text = element->GetText();

        if(text)
        {
           try
           {
              set_conditions_neurons_number(atoi(text));
           }
           catch(const std::logic_error& e)
           {
              std::cout << e.what() << std::endl;
           }
        }
     }
  }

  // Conditions method
  {
     const tinyxml2::XMLElement* element = document.FirstChildElement("ConditionsMethod");

     if(element)
     {
        const char* text = element->GetText();

        if(text)
        {
           try
           {
              std::string new_conditions_method(text);

              set_conditions_method(new_conditions_method);
           }
           catch(const std::logic_error& e)
           {
              std::cout << e.what() << std::endl;
           }
        }
     }
  }

  // Input values
  {
     const tinyxml2::XMLElement* element = document.FirstChildElement("InputValues");

     if(element)
     {
        const char* text = element->GetText();

        if(text)
        {
           try
           {
              Vector<double> new_external_input_values;
              new_external_input_values.parse(text);

              set_external_input_values(new_external_input_values);
           }
           catch(const std::logic_error& e)
           {
              std::cout << e.what() << std::endl;
           }
        }
     }
  }

  // Output values
  {
     const tinyxml2::XMLElement* element = document.FirstChildElement("OutputValues");

     if(element)
     {
        const char* text = element->GetText();

        if(text)
        {
           try
           {
              Vector<double> new_output_values_vector;
              new_output_values_vector.parse(text);

              const Matrix<double> new_output_values = new_output_values_vector.to_matrix(conditions_neurons_number, 2);

              set_output_values(new_output_values);
           }
           catch(const std::logic_error& e)
           {
              std::cout << e.what() << std::endl;
           }
        }
     }
  }

  // Display
  {
     const tinyxml2::XMLElement* element = document.FirstChildElement("Display");

     if(element)
     {
        const char* text = element->GetText();

        if(text)
        {
           try
           {
              const std::string string(text);

              set_display(string != "0");
           }
           catch(const std::logic_error& e)
           {
              std::cout << e.what() << std::endl;
           }
        }
     }
  }
}

}

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
