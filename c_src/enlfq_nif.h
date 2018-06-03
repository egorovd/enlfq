#pragma once
#include "erl_nif.h"

struct atoms
{
    ERL_NIF_TERM atomOk;
    ERL_NIF_TERM atomError;
    ERL_NIF_TERM atomTrue;
//    ERL_NIF_TERM atomFalse;
//    ERL_NIF_TERM atomUndefined;
    ERL_NIF_TERM atomEmpty;
};

struct shared_data
{
    ErlNifResourceType* resQueueInstance;
};

extern atoms ATOMS;
