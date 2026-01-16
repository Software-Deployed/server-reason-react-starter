module type DB = Caqti_lwt.CONNECTION;

module R = Caqti_request;
module T = Caqti_type;

[@deriving (yojson, fields)]
type article = {
  id: int,
  title: string,
  body: string,
  updated_at: string,
  created_at: string,
};

let add = {
  let req =
    R.exec(
      T.(tup5(int, string, string, string, string)),
      {|
        INSERT INTO articles (id, title, body, updated_at, created_at)
        VALUES (?, ?, ?, ?, ?)
      |},
    );
  (a, module Db: DB) => {
    let%lwt u = Db.exec(req, (a.id, a.title, a.body, a.updated_at, a.created_at));
    Caqti_lwt.or_fail(u);
  };
};

let getAll = {
  let req =
    R.collect(
      T.unit,
      T.(tup5(int, string, string, string, string)),
      {|
        SELECT id, title, body, updated_at, created_at FROM articles
        ORDER BY created_at DESC
      |},
    );
  (module Db: DB) => {
    let%lwt list_or_error = Db.collect_list(req, ());
    let raw = Caqti_lwt.or_fail(list_or_error);
    Lwt.map(
      lst =>
        lst
        |> List.map(((id, title, body, updated_at, created_at)) => {
             id, title, body, updated_at, created_at
           }),
      raw,
    );
  };
};

let getById = id => {
  let req =
    R.find_opt(
      T.int,
      T.(tup5(int, string, string, string, string)),
      {|
        SELECT id, title, body, updated_at, created_at
        FROM articles
        WHERE id = ?
      |},
    );
  (module Db: DB) => {
    let%lwt opt_or_error = Db.find_opt(req, id);
    let raw = Caqti_lwt.or_fail(opt_or_error);
    Lwt.map(
      opt =>
        switch (opt) {
        | Some((id, title, body, updated_at, created_at)) =>
          Some({id, title, body, updated_at, created_at})
        | None => None
        },
      raw,
    );
  };
};
