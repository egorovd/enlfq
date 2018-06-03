#pragma once

#include "erl_nif.h"

extern "C" {
void nif_enlfq_free(ErlNifEnv *env, void *obj);
ERL_NIF_TERM nif_enlfq_new(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]);
ERL_NIF_TERM nif_enlfq_push(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]);
ERL_NIF_TERM nif_enlfq_pop(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]);
}