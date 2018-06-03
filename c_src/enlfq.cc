//#include <string.h>
#include "enlfq.h"
#include "enlfq_nif.h"

#include "nif_utils.h"

#include "concurrentqueue.h"


struct q_item {
    ErlNifEnv *env;
    ERL_NIF_TERM term;
};

struct squeue {
    moodycamel::ConcurrentQueue<q_item> *queue;
};


void nif_enlfq_free(ErlNifEnv *, void *obj) {
    squeue *inst = static_cast<squeue *>(obj);

    if (inst != nullptr)
        delete inst->queue;
}

ERL_NIF_TERM nif_enlfq_new(ErlNifEnv *env, int, const ERL_NIF_TERM *) {
    shared_data *data = static_cast<shared_data *>(enif_priv_data(env));


    squeue *qinst = static_cast<squeue *>(enif_alloc_resource(data->resQueueInstance, sizeof(squeue)));
    qinst->queue = new moodycamel::ConcurrentQueue<q_item>;

    if (qinst == NULL)
        return make_error(env, "enif_alloc_resource failed");

    ERL_NIF_TERM term = enif_make_resource(env, qinst);
    enif_release_resource(qinst);
    return enif_make_tuple2(env, ATOMS.atomOk, term);
}

ERL_NIF_TERM nif_enlfq_push(ErlNifEnv *env, int, const ERL_NIF_TERM argv[]) {
    shared_data *data = static_cast<shared_data *>(enif_priv_data(env));

    squeue *inst;

    if (!enif_get_resource(env, argv[0], data->resQueueInstance, (void **) &inst)) {
        return enif_make_badarg(env);
    }

    q_item item;

    item.env = enif_alloc_env();
    item.term = enif_make_copy(item.env, argv[1]);

    inst->queue->enqueue(item);

    return ATOMS.atomTrue;
}

ERL_NIF_TERM nif_enlfq_pop(ErlNifEnv *env, int, const ERL_NIF_TERM argv[]) {
    shared_data *data = static_cast<shared_data *>(enif_priv_data(env));
    squeue *inst = NULL;

    if (!enif_get_resource(env, argv[0], data->resQueueInstance, (void **) &inst)) {
        return enif_make_badarg(env);
    }

    ERL_NIF_TERM term;
    q_item item;

    if (inst->queue->try_dequeue(item)) {
        term = enif_make_copy(env, item.term);
        enif_free_env(item.env);
        return enif_make_tuple2(env, ATOMS.atomOk, term);
    } else {
        return ATOMS.atomEmpty;
    }

}
