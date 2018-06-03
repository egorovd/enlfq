-module(enlfq).

-on_load(load_nif/0).

-define(NOT_LOADED, not_loaded(?LINE)).

%% API exports
-export([new/0, push/2, pop/1]).

%%====================================================================
%% API functions
%%====================================================================


-spec(new() -> {ok, QueueRef :: reference()} | badarg | {error, Reason :: binary()}).
new() ->
  ?NOT_LOADED.

-spec(push(QueueRef :: reference(), Data :: any()) ->
  true | {error, Reason :: binary()}).
push(_QueueRef, _Data) ->
  ?NOT_LOADED.

-spec(pop(QueueRef :: reference()) ->
  {ok, Data :: any()} | empty | {error, Reason :: binary()}).
pop(_QueueRef) ->
  ?NOT_LOADED.

%%====================================================================
%% Internal functions
%%====================================================================


%% nif functions

load_nif() ->
  SoName = get_priv_path(?MODULE),
  io:format(<<"Loading library: ~p ~n">>, [SoName]),
  ok = erlang:load_nif(SoName, 0).

get_priv_path(File) ->
  case code:priv_dir(?MODULE) of
    {error, bad_name} ->
      Ebin = filename:dirname(code:which(?MODULE)),
      filename:join([filename:dirname(Ebin), "priv", File]);
    Dir ->
      filename:join(Dir, File)
  end.

not_loaded(Line) ->
  erlang:nif_error({not_loaded, [{module, ?MODULE}, {line, Line}]}).