//
//  bp.hpp
//  beliefprop
//
//  Created by Benjamin Walker on 2/19/18.
//  Copyright © 2018 Benjamin Walker. All rights reserved.
//

#ifndef bp_hpp
#define bp_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <random>
#include <time.h>

using namespace std;

typedef unsigned char byte;
typedef unsigned long index_t;

void print_array(index_t *arr, index_t n);

class BP_Modularity
{
public:
    // initialize with Erdos-Renyi random graph
	BP_Modularity(const vector<pair<index_t, index_t> > &edgelist, const index_t _n, const int q, const double beta, const double resgamma = 1.0, bool verbose = false, bool transform = false);
    ~BP_Modularity();
    
    // run BP to convergence
    long run(unsigned long maxIters=100);
	
    // run one pass of the belief propagation update
    void step();
    
    void compute_marginals();
    double compute_bethe_free_energy();
    double compute_factorized_free_energy();
    
    vector<vector<double> > return_marginals();
    
    // accessors
    double getBeta() const { return beta; };
    void setBeta(double in, bool reset=true);
    
    index_t getq() const { return q; };
    void setq(double new_q);
    
    bool getVerbose() const { return verbose; };
    void setVerbose(bool in) { verbose = in; };
private:
    void initializeBeliefs();
    void initializeTheta();
    void normalize(double *beliefs, index_t i);
    
    vector<unordered_map<index_t,index_t> > neighbor_offset_map;
    vector<index_t> neighbor_count;
    
    // private variables
    double * beliefs;
    double * beliefs_old;     // for out-of-place updates
    size_t * beliefs_offsets;
    
    index_t * neighbors;
    index_t * neighbors_reversed;
    size_t * neighbors_offsets;
    
    double * scratch;
    
    double * marginals;
	double * marginals_old;
    
    vector<double> theta;
    
    index_t n;
    int q;
    double beta;
    double resgamma;
    
    bool transform;
    vector<index_t> isomorphism;
    vector<index_t> r_isomorphism;
    
    index_t max_degree;
    
    unsigned long num_edges;
    
    double change;
    vector<double> changes;
    vector<index_t> order;
    
    double scale;
    double prefactor;
    
    double eps;
    
    bool changed;
    bool computed_marginals;
    
    inline index_t n_neighbors(index_t i) { return (index_t) neighbors_offsets[i+1]-neighbors_offsets[i]; }
    
    void print_neighbors(index_t k) { print_array(neighbors+neighbors_offsets[k],n_neighbors(k));}
    
    default_random_engine rng;

	void compute_marginal(index_t i);
    
    bool verbose;
};

#endif /* bp_hpp */
