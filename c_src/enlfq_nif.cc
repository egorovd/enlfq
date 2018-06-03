#include "enlfq_nif.h"
#include "enlfq.h"
#include "nif_utils.h"

const char kAtomOk[] = "ok";
const char kAtomError[] = "error";
const char kAtomTrue[] = "true";
//const char kAtomFalse[] = "false";
//const char kAtomUndefined[] = "undefined";
const char kAtomEmpty[] = "empty";

atoms ATOMS;

void open_resources(ErlNifEnv *env, shared_data *data) {
    ErlNifResourceFlags flags = static_cast<ErlNifResourceFlags>(ERL_NIF_RT_CREATE | ERL_NIF_RT_TAKEOVER);
    data->resQueueInstance = enif_open_resource_type(env, NULL, "enlfq_instance", nif_enlfq_free, flags, NULL);
}

int on_nif_load(ErlNifEnv *env, void **priv_data, ERL_NIF_TERM) {

    ATOMS.atomOk = make_atom(env, kAtomOk);
    ATOMS.atomError = make_atom(env, kAtomError);
    ATOMS.atomTrue = make_atom(env, kAtomTrue);
//    ATOMS.atomFalse = make_atom(env, kAtomFalse);
//    ATOMS.atomUndefined = make_atom(env, kAtomUndefined);
    ATOMS.atomEmpty = make_atom(env, kAtomEmpty);

    shared_data *data = static_cast<shared_data *>(enif_alloc(sizeof(shared_data)));
    open_resources(env, data);

    *priv_data = data;
    return 0;
}

void on_nif_unload(ErlNifEnv *, void *priv_data) {
    shared_data *data = static_cast<shared_data *>(priv_data);
    enif_free(data);
}

int on_nif_upgrade(ErlNifEnv *env, void **priv, void **, ERL_NIF_TERM) {
    shared_data *data = static_cast<shared_data *>(enif_alloc(sizeof(shared_data)));
    open_resources(env, data);

    *priv = data;
    return 0;
}

static ErlNifFunc nif_funcs[] =
        {
                {"new",  0, nif_enlfq_new},
                {"push", 2, nif_enlfq_push},
                {"pop",  1, nif_enlfq_pop}
        };

ERL_NIF_INIT(enlfq, nif_funcs, on_nif_load, NULL, on_nif_upgrade, on_nif_unload)

