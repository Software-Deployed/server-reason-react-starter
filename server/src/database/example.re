module type DB = Caqti_lwt.CONNECTION;

module R = Caqti_request;
module T = Caqti_type;

type key = string;
[@deriving (yojson, fields, csv)]
type t = {
  email: string,
  password: string,
};

let add = {
  let query =
    R.exec(T.tup2(T.string, T.string), "INSERT INTO user VALUES (?, ?)");

  (u, module Db: DB) => {
    let%lwt unit_or_error = Db.exec(query, (u.email, u.password));
    Caqti_lwt.or_fail(unit_or_error);
  };
};

let get = email => {
  let query =
    R.find_opt(T.string, T.(tup2(string, string)), "SELECT * FROM example");

  (module Db: DB) => {
    let%lwt unit_or_error = Db.find_opt(query, email);
    let raw = Caqti_lwt.or_fail(unit_or_error);
    Lwt.bind(raw, u =>
      Lwt.return(
        switch (u) {
        | Some((email, password)) =>
          Some({
            email,
            password,
          })
        | None => None
        },
      )
    );
  };
};
