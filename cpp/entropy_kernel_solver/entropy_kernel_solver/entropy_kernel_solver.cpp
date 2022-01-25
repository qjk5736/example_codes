//
// Copyright 2021 John I Krassikoff
//
// This program is free software : you can redistribute itand /or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < https://www.gnu.org/licenses/>.
//

#include "entropy_kernel_solver.h"
#include <vector>
#include <limits>
#include <cmath>

double entropy_kernel_solver::callEntropySolver( const int Value[], const int k_elements)
{
	// This function calculates the entropy value of the input kernal.
	auto Log2 = [](double n) { return std::log(n) / std::log(2.); };
	// Shift index by +1 for Octave, 0 for C++.
	int shift = 0;
	int i = shift;
	int j = shift;
	int k = shift;
	int startlndex = shift;
	double result = 0.0;
	int arrayMax = k_elements;
	std::vector<int> valuelndex(k_elements);
	std::vector<std::vector<double> > remlndex(3, std::vector<double>(k_elements));
	for( i = shift; i < arrayMax; i++ )
	{
		valuelndex[i] = -1;
		remlndex[shift][i] = -1.0;
		remlndex[shift+1][i] = -1.0;
		remlndex[shift+2][i] = -1.0;
	}
	int localValue = Value[shift];
	valuelndex[shift] = 0;
	bool first = true;
	startlndex = shift;
	i = shift;
	j = shift;
	k = 0;
	bool alreadyUsed = false;

	while( ( i < arrayMax ) && ( localValue > -1.0 ) && ( j <= arrayMax ))
	{
		for( int q = shift; q < arrayMax; q++ )
		{
			if( Value[j] == remlndex[(shift+1)][q]) alreadyUsed = true;
		}
		if( alreadyUsed == false )
		{
			while( j <= arrayMax )
			{
				if( localValue == Value[j] )
				{
					valuelndex[i] = j;
					k = k + 1;
				}
				else
				{
					if( first ) startlndex = j;
					first = false;
				}
				j = j + 1;
			}
			remlndex[shift][i] = static_cast<double>( k );
			remlndex[(shift+1)] [i] = static_cast<double>( localValue );
			i = i + 1;
		}
		else
		{
			startlndex += 1;
		}
		j = startlndex;
		if( j <= arrayMax)
		{
			localValue = Value[j];
		}
		first = true;
		k = 0;
		alreadyUsed = false;
	}

	int numBins = i - 1;

	double sum = 0.0;
	result = 0.0;
	i = shift;
	for( i = shift; i < numBins; i++)
	{
		sum += remlndex[shift][i];
	}
	if( sum > 0.000001)
	{
		for( i = shift; i < numBins; i++ )
		{
			remlndex[(shift+2)][i] = remlndex[shift][i]/sum;
		}
		i = shift;
		for( i = shift; i < numBins; i++ )
		{
			if( remlndex[(shift+2)][i] > 
				2.0* static_cast<double>(std::numeric_limits<float>::epsilon()))
			{
				result -= remlndex[(shift+2)][i]*
					static_cast<double>( Log2(remlndex[(shift+2)][i] ) );
			}
		}
	}
	return result;
}
