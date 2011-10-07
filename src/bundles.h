//
//  bundles.h
//  express
//
//  Created by Adam Roberts on 9/6/11.
//  Copyright 2011 Adam Roberts. All rights reserved.
//

#ifndef express_bundles_h
#define express_bundles_h

#include <vector>
#include <boost/unordered_set.hpp>


class Transcript;
class FragMassTable;

/** 
 * The Bundle class keeps track of a group of transcripts that have shared ambiguous (multi-mapped)
 * reads. Besides storing the transcript, it keeps track of the number of observed fragments,
 * the total fragment mass, and the next fragment mass (which it also updates).
 *  @author    Adam Roberts
 *  @date      2011
 *  @copyright Artistic License 2.0
 **/
class Bundle
{
    /**
     * a private vector that stores pointers to all transcripts in the bundle
     */
    std::vector<Transcript*> _transcripts;     
    
    /**
     * a private size_t that stores the total number of observed fragments mapped to the bundle
     */
    size_t _counts;

    
public:
    
    /**
     * Bundle Constructor.
     * @param trans a pointer to the initial Transcript object in the bundle
     * @param fmt a pointer to the (global) FragMassTable
     */
    Bundle(Transcript* trans);
        
    /**
     * a member function that increases the total bundle observed fragment counts by a given amount
     * @param incr_amt the amount to increase the counts by
     */
    void incr_counts(size_t incr_amt=1);
    
    /**
     * a member function that returns the number of transcripts in the bundle
     * @return the number of transcripts in the bundle
     */
    size_t size() const { return _transcripts.size(); }
    
    /**
     * a member function that returns a reference to the vector of pointers to transcripts in the bundle
     * @return reference to the vector pointing to bundle transcripts
     */
    std::vector<Transcript*>& transcripts() { return _transcripts; }
    
    /**
     * a member function that returns the total number of observed fragments mapped to transcripts in the bundle
     * @return the total number of fragments mapped to transcripts in the bundle
     */
    size_t counts() const { return _counts; }
};


typedef boost::unordered_set<Bundle*> BundleSet;

/** 
 * The BundleTable class keeps track of the Bundle objects for a given run.  It has the ability to create, delete,
 * and merge bundles. It also keeps track of the transcript covariances, since these are related to bundles in that
 * all covariances outside of a bundle are nonzero.
 *  @author    Adam Roberts
 *  @date      2011
 *  @copyright Artistic License 2.0
 **/
class BundleTable
{
    /**
     * a private unordered_set to store all of the bundles
     */
    BundleSet _bundles;

public:
    
    /**
     * BundleTable constructor.
     * @param fmt a pointer to the (global) FragMassTable
     */
    BundleTable();
    
    /**
     * BundleTable deconstructor.  Deletes all Bundle objects.
     */
    ~BundleTable();
    
    /**
     * a member function that returns the set of current Bundle objects
     * @return a reference to the unordered_set containing all current Bundle objects
     */
    const BundleSet& bundles() const { return _bundles; }
    
    /**
     * a member function that returns the size of the set of current Bundle objects,
     * which is the current number of bundles
     * @return the current number of bundles
     */    
    size_t size() const { return _bundles.size(); }
    
    /**
     * a member function that creates a new bundle, initially with only the single given Transcript
     * @param trans a pointer to the only Transcript initially contained in the Bundle
     * @return a pointer to the new Bundle object
     */ 
    Bundle* create_bundle(Transcript* trans);
    
    /**
     * a member function that merges two Bundle objects into one
     * the Transcripts are all move to the larger bundles and the other is deleted
     * @param b1 a pointer to one of the Bundle objects to merge
     * @param b2 a pointer to the other Bundle object to merge
     * @return a pointer to the merged Bundle object
     */ 
    Bundle* merge(Bundle* b1, Bundle* b2);
};


#endif
