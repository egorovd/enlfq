enlfq
=====

A simple NIF Queue using the library: [concurrentqueue](https://github.com/cameron314/concurrentqueue/tree/8f7e861dd9411a0bf77a6b9de83a47b3424fafba)

Build
-----

    $ rebar3 compile


Using
-----

<<<<<<< HEAD
```erlang
=======
    ```erlang
>>>>>>> b9e3c0860a515ca86a1635a5721a6cb165f8007a

    {ok, Q} = enlfq:new().

    T =  {any, term, [], #{}, 1}.

    true =enlfq:push(Q,T).

    {ok, T} = enlfq:pop(Q).

    empty = enlfq:pop(Q).

```




