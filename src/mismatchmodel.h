#ifndef MISMATCH_H
#define MISMATCH_H
//
//  mismatchmodel.h
//  express
//
//  Created by Adam Roberts on 4/23/11.
//  Copyright 2011 Adam Roberts. All rights reserved.
//

#include "frequencymatrix.h"

class FragMap;
class Transcript;

/** 
 * The MismatchTable class is used to store and update mismatch (error) parameters using a first-order
 * Markov model based on nucleotide and position in a ride and to return likelihoods of mismatches in given reads.  
 * All values are stored and returned in log space. 
 *  @author    Adam Roberts
 *  @date      2011
 *  @copyright Artistic License 2.0
 **/
class MismatchTable
{
    /**
     * a vector of FrequencyMatrix objects to store the Markov model parameters for each position in the first ("left") read 
     */
    std::vector<FrequencyMatrix> _first_read_mm;
    
    /**
     * a vector of FrequencyMatrix objects to store the Markov model parameters for each position in the second ("right") read 
     */
    std::vector<FrequencyMatrix> _second_read_mm;

public:
   
    /**
     * MismatchTable constructor initializes the model parameters using the specified (non-logged) pseudo-counts.
     * @param alpha a double containing the non-logged pseudo-counts for parameter initialization
     */
    MismatchTable(double alpha);
    
    /**
     * member function returns the log likeihood of mismatches in the mapping given the current error model paramaters
     * @param f the fragment mapping to calculate the log likelihood for
     * @return the log likelihood of the mapping based on mismatches
     */
    double log_likelihood(const FragMap& f) const;
    
    /**
     * member function that updates the error model parameters based on a mapping and its (logged) mass
     * @param f the fragment mapping 
     * @param mass the logged mass to increase the parameters by
     */
    void update(const FragMap&, double mass);
    
    /**
     * member function that returns a string containing a collapsed confusion matrix based on the model parameters for the first read
     * @return a space-separated string for the flattened, collapsed confusion matrix in row-major format (observed value as rows)
     */
    std::string to_string() const;
    
    /**
     * a member function that outputs the final model parameters in a tab-separated file
     * the file has 1 row for each read position and the parameters are in columns indexed 
     * as (ref, prev, obs) in base 4 with A,C,G,T encoded as 0,1,2,3.
     * @param filename to write the file to
     */
    void output(std::string filename);
};

#endif