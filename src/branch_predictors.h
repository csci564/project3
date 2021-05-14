//
// This file defines the function signatures necessary for creating a branch
// predictor and defines the branch predictor struct.
//

#ifndef BRANCH_PREDICTORS_H
#define BRANCH_PREDICTORS_H

#include <stdbool.h>
#include <stdlib.h>

#include "branch_metadata.h"
#include "util.h"

// This struct describes the functionality of a branch predictor. The function
// pointers describe the three functions that every branch predictor must
// implement. Arbitrary data can be stored in the data pointer and can be used
// to store the state of the branch predictor between calls to predict and
// handle_result.
//
// For those of you who are unfamiliar with function pointers, they take the
// form:
//
//      return_type (*function_name)(list of arguments)
struct branch_predictor {
    // This function is called to get a prediction from the branch predictor as
    // to whether or not the branch is taken.
    //
    // Arguments
    //  * branch_predictor: the instance of branch_predictor to clean up.
    //  * address: the branch instruction address.
    //
    // Returns (enum branch_direction): the predicted branch direction
    enum branch_direction (*predict)(struct branch_predictor *branch_predictor, uint32_t address);

    // This function is called after a branch was taken or not taken so that
    // the branch predictor can update its state.
    //
    // Arguments
    //  * branch_predictor: the instance of branch_predictor to clean up.
    //  * address: the branch instruction address.
    //  * address: the actual direction that the branch went.
    void (*handle_result)(struct branch_predictor *branch_predictor, uint32_t address,
                          enum branch_direction branch_direction);

    // This function is called right before the branch predictor is
    // deallocated. You should perform any necessary cleanup operations here.
    // (This is where you should free the branch_predictor->data, for example.)
    //
    // Arguments:
    //  * branch_predictor: the instance of branch_predictor to clean up.
    void (*cleanup)(struct branch_predictor *branch_predictor);

    // Use this pointer to store any data that the branch predictor needs.
    void *data;
};

struct branch_predictor *ant_branch_predictor_new(uint32_t num_branches,
                                                  struct branch_metadata *branch_metadatas);
struct branch_predictor *at_branch_predictor_new(uint32_t num_branches,
                                                 struct branch_metadata *branch_metadatas);
struct branch_predictor *btfnt_branch_predictor_new(uint32_t num_branches,
                                                    struct branch_metadata *branch_metadatas);
struct branch_predictor *ltg_branch_predictor_new(uint32_t num_branches,
                                                  struct branch_metadata *branch_metadatas);
struct branch_predictor *ltl_branch_predictor_new(uint32_t num_branches,
                                                  struct branch_metadata *branch_metadatas);
struct branch_predictor *tbg_branch_predictor_new(uint32_t num_branches,
                                                  struct branch_metadata *branch_metadatas);
struct branch_predictor *tbl_branch_predictor_new(uint32_t num_branches,
                                                  struct branch_metadata *branch_metadatas);

#endif
