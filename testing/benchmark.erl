-module(benchmark).
-author("silviu.caragea").

-export([
    benchmark_serial/2,
    benchmark_concurrent/3
]).

benchmark_serial(Elements, MaxPriority) ->
    rand:uniform(), %just to init the seed
    {ok, Q} = enlfq:new(),

    {T0, ok} = timer:tc(fun() -> insert_none(Elements, MaxPriority) end),
    {T1, ok} = timer:tc(fun() -> insert_item(Elements, Q, MaxPriority) end),
    {T2, ok} = timer:tc(fun() -> remove_item(Q) end),

    T0Ms = T0/1000,
    T1Ms = T1/1000,
    T2Ms = T2/1000,

    io:format(<<"insert overhead: ~p ms insert time: ~p ms pop time: ~p ms ~n">>, [T0Ms, T1Ms, T2Ms]).

benchmark_concurrent(Procs, Elements, MaxPriority) ->
    {ok, Q} = enlfq:new(),

    ElsPerProcess = round(Elements/Procs),

    InsertNoneWorkFun = fun() ->
        insert_none(ElsPerProcess, MaxPriority)
    end,

    InsertWorkFun = fun() ->
        insert_item(ElsPerProcess, Q, MaxPriority)
    end,

    RemoveWorkFun = fun() ->
        remove_item(Q)
    end,

    {T0, _} = timer:tc(fun()-> multi_spawn:do_work(InsertNoneWorkFun, Procs) end),
    {T1, _} = timer:tc(fun()-> multi_spawn:do_work(InsertWorkFun, Procs) end),
    {T2, _} = timer:tc(fun()-> multi_spawn:do_work(RemoveWorkFun, Procs) end),

    T0Ms = T0/1000,
    T1Ms = T1/1000,
    T2Ms = T2/1000,

    io:format(<<"insert overhead: ~p ms insert time: ~p ms pop time: ~p ms ~n">>, [T0Ms, T1Ms, T2Ms]).

insert_item(0, _Q, _Max) ->
    ok;
insert_item(N, Q, Max) ->
%%    El = rand:uniform(Max),
    true = enlfq:push(Q,{}),
    insert_item(N-1, Q, Max).

remove_item(Q) ->
    case enlfq:pop(Q) of
        empty ->
            ok;
        {ok, _} ->
            remove_item(Q)
    end.

insert_none(0, _Max) ->
    ok;
insert_none(N, Max) ->
%%    rand:uniform(Max),
    insert_none(N-1, Max).


