
#ifndef OPTIMAL_SOLUTIONS_H
#define OPTIMAL_SOLUTIONS_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <cmath>

#include "WFG_Toolkit/ExampleProblems.h"
#include "WFG_Toolkit/ExampleShapes.h"
#include "WFG_Toolkit/TransFunctions.h"

using namespace WFG::Toolkit;
using namespace WFG::Toolkit::Examples;
using std::vector;
using std::string;

namespace
{

//** Using a uniform random distribution, generate a number in [0,bound]. ***

double next_double( const double bound = 1.0 )
{
  assert( bound > 0.0 );

  return bound * genrand() / static_cast< double >( RAND_MAX );
}

//** Create a random Pareto optimal solution for WFG1. **********************

vector< double > WFG_1_random_soln( const int k, const int l )
{
  vector< double > result;  // the result vector


  //---- Generate a random set of position parameters.

  for( int i = 0; i < k; i++ )
  {
    // Account for polynomial bias.
    result.push_back( pow( next_double(), 50.0 ) );
  }


  //---- Set the distance parameters.

  for( int i = k; i < k+l; i++ )
  {
    result.push_back( 0.35 );
  }


  //---- Scale to the correct domains.

  for( int i = 0; i < k+l; i++ )
  {
    result[i] *= 2.0*(i+1);
  }


  //---- Done.

  return result;
}


//** Create a random Pareto optimal solution for WFG2-WFG7. *****************

vector< double > WFG_2_thru_7_random_soln( const int k, const int l )
{
  vector< double > result;  // the result vector


  //---- Generate a random set of position parameters.

  for( int i = 0; i < k; i++ )
  {
    result.push_back( next_double() );
  }


  //---- Set the distance parameters.

  for( int i = k; i < k+l; i++ )
  {
    result.push_back( 0.35 );
  }


  //---- Scale to the correct domains.

  for( int i = 0; i < k+l; i++ )
  {
    result[i] *= 2.0*(i+1);
  }


  //---- Done.

  return result;
}


//** Create a random Pareto optimal solution for WFG8. **********************

vector< double > WFG_8_random_soln( const int k, const int l )
{
  vector< double > result;  // the result vector


  //---- Generate a random set of position parameters.

  for( int i = 0; i < k; i++ )
  {
    result.push_back( next_double() );
  }


  //---- Calculate the distance parameters.

  for( int i = k; i < k+l; i++ )
  {
    const vector< double >  w( result.size(), 1.0 );
    const double u = TransFunctions::r_sum( result, w  );

    const double tmp1 = fabs( floor( 0.5 - u ) + 0.98/49.98 );
    const double tmp2 = 0.02 + 49.98*( 0.98/49.98 - ( 1.0 - 2.0*u )*tmp1 );

    result.push_back( pow( 0.35, pow( tmp2, -1.0 ) ));
  }


  //---- Scale to the correct domains.

  for( int i = 0; i < k+l; i++ )
  {
    result[i] *= 2.0*(i+1);
  }


  //---- Done.

  return result;
}


//** Create a random Pareto optimal solution for WFG9. **********************

vector< double > WFG_9_random_soln( const int k, const int l )
{
  vector< double > result( k+l );  // the result vector


  //---- Generate a random set of position parameters.

  for( int i = 0; i < k; i++ )
  {
    result[i] = next_double();
  }


  //---- Calculate the distance parameters.

  result[k+l-1] = 0.35;  // the last distance parameter is easy

  for( int i = k+l-2; i >= k; i-- )
  {
    vector< double > result_sub;
    for( int j = i+1; j < k+l; j++ )
    {
      result_sub.push_back( result[j] );
    }

    const vector< double > w( result_sub.size(), 1.0 );
    const double tmp1 = TransFunctions::r_sum( result_sub, w  );

    result[i] = pow( 0.35, pow( 0.02 + 1.96*tmp1, -1.0 ) );
  }


  //---- Scale to the correct domains.

  for( int i = 0; i < k+l; i++ )
  {
    result[i] *= 2.0*(i+1);
  }


  //---- Done.

  return result;
}


//** Create a random Pareto optimal solution for I1. *****************

vector< double > I1_random_soln( const int k, const int l )
{
  vector< double > result;  // the result vector


  //---- Generate a random set of position parameters.

  for( int i = 0; i < k; i++ )
  {
    result.push_back( next_double() );
  }


  //---- Set the distance parameters.

  for( int i = k; i < k+l; i++ )
  {
    result.push_back( 0.35 );
  }


  //---- Done.

  return result;
}


//** Create a random Pareto optimal solution for I2. **********************

vector< double > I2_random_soln( const int k, const int l )
{
  vector< double > result( k+l );  // the result vector


  //---- Generate a random set of position parameters.

  for( int i = 0; i < k; i++ )
  {
    result[i] = next_double();
  }


  //---- Calculate the distance parameters.

  result[k+l-1] = 0.35;  // the last distance parameter is easy

  for( int i = k+l-2; i >= k; i-- )
  {
    vector< double > result_sub;
    for( int j = i+1; j < k+l; j++ )
    {
      result_sub.push_back( result[j] );
    }

    const vector< double > w( result_sub.size(), 1.0 );
    const double tmp1 = TransFunctions::r_sum( result_sub, w  );

    result[i] = pow( 0.35, pow( 0.02 + 1.96*tmp1, -1.0 ) );
  }


  //---- Done.

  return result;
}


//** Create a random Pareto optimal solution for I3. **********************

vector< double > I3_random_soln( const int k, const int l )
{
  vector< double > result;  // the result vector


  //---- Generate a random set of position parameters.

  for( int i = 0; i < k; i++ )
  {
    result.push_back( next_double() );
  }


  //---- Calculate the distance parameters.

  for( int i = k; i < k+l; i++ )
  {
    const vector< double >  w( result.size(), 1.0 );
    const double u = TransFunctions::r_sum( result, w  );

    const double tmp1 = fabs( floor( 0.5 - u ) + 0.98/49.98 );
    const double tmp2 = 0.02 + 49.98*( 0.98/49.98 - ( 1.0 - 2.0*u )*tmp1 );

    result.push_back( pow( 0.35, pow( tmp2, -1.0 ) ));
  }


  //---- Done.

  return result;
}


//** Create a random Pareto optimal solution for I4. **********************

vector< double > I4_random_soln( const int k, const int l )
{
  return I1_random_soln( k, l );
}


//** Create a random Pareto optimal solution for I5. **********************

vector< double > I5_random_soln( const int k, const int l )
{
  return I3_random_soln( k, l );
}


//** Generate a random solution for a given problem. ************************

vector< double > problem_random_soln
(
  const int k,
  const int l,
  const std::string fn
)
{
  if ( fn == "WFG1" )
  {
    return WFG_1_random_soln( k, l );
  }
  else if
  (
    fn == "WFG2" ||
    fn == "WFG3" ||
    fn == "WFG4" ||
    fn == "WFG5" ||
    fn == "WFG6" ||
    fn == "WFG7"
  )
  {
    return WFG_2_thru_7_random_soln( k, l );
  }
  else if ( fn == "WFG8" )
  {
    return WFG_8_random_soln( k, l );
  }
  else if ( fn == "WFG9" )
  {
    return WFG_9_random_soln( k, l );
  }
  else if ( fn == "I1" )
  {
    return I1_random_soln( k, l );
  }
  else if ( fn == "I2" )
  {
    return I2_random_soln( k, l );
  }
  else if ( fn == "I3" )
  {
    return I3_random_soln( k, l );
  }
  else if ( fn == "I4" )
  {
    return I4_random_soln( k, l );
  }
  else if ( fn == "I5" )
  {
    return I5_random_soln( k, l );
  }
  else
  {
    assert( false );
    return vector< double >();
  }
}

//** Generate a random solution for a given problem. ************************

vector< double > problem_optimal_soln
(
  const vector< double >& y,
  const std::string fn
)
{
  if ( fn == "WFG1" )
  {
    return Shapes::WFG1_shape( y );
  }
  else if ( fn == "WFG2" )
  {
    return Shapes::WFG2_shape( y );
  }
  else if ( fn == "WFG3" )
  {
    return Shapes::WFG3_shape( y );
  }
  else if
  (
    fn == "WFG4" ||
    fn == "WFG5" ||
    fn == "WFG6" ||
    fn == "WFG7" ||
    fn == "WFG8" ||
    fn == "WFG9"
  )
  {
    return Shapes::WFG4_shape( y );
  }
  else if
  (
    fn == "I1" ||
    fn == "I2" ||
    fn == "I3" ||
    fn == "I4" ||
    fn == "I5"
  )
  {
    return Shapes::I1_shape( y );
  }
  else
  {
    assert( false );
    return vector< double >();
  }
}

//** Calculate the fitness for a problem given some parameter set. **********

vector< double > problem_calc_fitness
(
  const vector< double >& z,
  const int k,
  const int M,
  const std::string fn
)
{
  if ( fn == "WFG1" )
  {
    return Problems::WFG1( z, k, M );
  }
  else if ( fn == "WFG2" )
  {
    return Problems::WFG2( z, k, M );
  }
  else if ( fn == "WFG3" )
  {
    return Problems::WFG3( z, k, M );
  }
  else if ( fn == "WFG4" )
  {
    return Problems::WFG4( z, k, M );
  }
  else if ( fn == "WFG5" )
  {
    return Problems::WFG5( z, k, M );
  }
  else if ( fn == "WFG6" )
  {
    return Problems::WFG6( z, k, M );
  }
  else if ( fn == "WFG7" )
  {
    return Problems::WFG7( z, k, M );
  }
  else if ( fn == "WFG8" )
  {
    return Problems::WFG8( z, k, M );
  }
  else if ( fn == "WFG9" )
  {
    return Problems::WFG9( z, k, M );
  }
  else if ( fn == "I1" )
  {
    return Problems::I1( z, k, M );
  }
  else if ( fn == "I2" )
  {
    return Problems::I2( z, k, M );
  }
  else if ( fn == "I3" )
  {
    return Problems::I3( z, k, M );
  }
  else if ( fn == "I4" )
  {
    return Problems::I4( z, k, M );
  }
  else if ( fn == "I5" )
  {
    return Problems::I5( z, k, M );
  }
  else
  {
    assert( false );
    return vector< double >();
  }
}

}  // unnamed namespace

#endif
