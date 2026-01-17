let _doc_root = Sys.getenv_opt "DOC_ROOT" |> Option.value ~default:"./"

let () =
  Dream.run ~port:8899 @@ Dream.logger
  @@ Dream.sql_pool "sqlite3:example.db"
  @@ Dream.router
       [
         Dream.get "/" (fun req ->
             let%lwt articles = Dream.sql req Database.Article.get_all in
             Dream.stream
               ~headers:[ ("Content-Type", "text/html") ]
               (fun response_stream ->
                 let pipe data =
                   let%lwt () = Dream.write response_stream data in
                   Dream.flush response_stream
                 in
                 let%lwt stream, _abort =
                   ReactDOM.renderToStream
                     (App.createElement ~articles ~children:[] () [@JSX])
                 in
                 Lwt_stream.iter_s pipe stream));
       ]
