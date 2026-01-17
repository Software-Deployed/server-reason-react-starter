open Caqti_request.Infix;

module type DB = Caqti_lwt.CONNECTION;

module R = Caqti_request;
module T = Caqti_type.Std;

let article = T.(t5(int, string, string, float, float));

let add =
  T.t2(T.string, T.string)
  ->. T.unit @@
  "INSERT INTO articles (title, body, updated_at, created_at) VALUES (?, ?, NOW(), NOW())";

let get_all = {
  let query =
    (T.unit ->* article)(
      "SELECT id, title, body, updated_at, created_at FROM articles ORDER BY created_at DESC",
    );
  (module Db: DB) => {
    let%lwt articles_or_error = Db.collect_list(query, ());
    Caqti_lwt.or_fail(articles_or_error);
  };
};

let get_by_id =
  T.int
  ->? article @@
  "SELECT id, title, body, updated_at, created_at FROM articles WHERE id = ?";
