let _doc_root = Sys.getenv_opt "DOC_ROOT" |> Option.value ~default:"./"

let articles_to_json articles =
  `List
    (List.map
       (fun (a : Example.article) ->
         `Assoc
           [
             ("id", `Int a.id);
             ("title", `String a.title);
             ("body", `String a.body);
             ("updated_at", `String a.updated_at);
             ("created_at", `String a.created_at);
           ])
       articles)

let () =
  Dream.run ~port:8899 @@ Dream.logger
  @@ Dream.router
       [
         Dream.get "/" (fun _req ->
             let%lwt articles =
               Example.get_all () |> Dream.sql ~reset:true ~params:()
             in
             let articles_json = articles_to_json articles in
             Dream.stream
               ~headers:[ ("Content-Type", "text/html") ]
               (fun response_stream ->
                 let pipe data =
                   let%lwt () = Dream.write response_stream data in
                   Dream.flush response_stream
                 in
                 let%lwt stream, _abort =
                   ReactDOM.renderToStream
                     (App.make ~props:[ ("articles", articles_json) ] ())
                 in
                 Lwt_stream.iter_s pipe stream));
       ]
