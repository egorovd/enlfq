enlfq
=====

A simple NIF Queue using the library: [moodycamel::concurrentqueue](https://github.com/cameron314/concurrentqueue/tree/8f7e861dd9411a0bf77a6b9de83a47b3424fafba)

#### moodycamel::ConcurrentQueue

An industrial-strength lock-free queue for C++.

Note: If all you need is a single-producer, single-consumer queue, I have one of those too.
Features

* Knock-your-socks-off blazing fast performance.
* Single-header implementation. Just drop it in your project.
* Fully thread-safe lock-free queue. Use concurrently from any number of threads.
* C++11 implementation -- elements are moved (instead of copied) where possible.
* Templated, obviating the need to deal exclusively with pointers -- memory is managed for you.
* No artificial limitations on element types or maximum count.
* Memory can be allocated once up-front, or dynamically as needed.
* Fully portable (no assembly; all is done through standard C++11 primitives).
* Supports super-fast bulk operations.
* Includes a low-overhead blocking version (BlockingConcurrentQueue).
* Exception safe.


Build
-----

    $ rebar3 compile


Using
-----

```erlang

    {ok, Q} = enlfq:new().

    T =  {any, term, [], #{}, 1}.

    true = enlfq:push(Q,T).

    {ok, T} = enlfq:pop(Q).

    empty = enlfq:pop(Q).
```




