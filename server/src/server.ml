let _doc_root = Sys.getenv_opt "DOC_ROOT" |> Option.value ~default:"./"

let () =
  Dream.run ~port:8899 @@ Dream.logger
  @@ Dream.router
       [
         Dream.get "/" (fun _req ->
             Dream.stream
               ~headers:[ ("Content-Type", "text/html") ]
               (fun response_stream ->
                 let pipe data =
                   let%lwt () = Dream.write response_stream data in
                   Dream.flush response_stream
                 in
                 let%lwt stream, _abort =
                   ReactDOM.renderToStream (App.make ())
                 in
                 Lwt_stream.iter_s pipe stream));
       ]
