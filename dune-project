(lang dune 3.20)

(name server-reason-react-starter)

(generate_opam_files true)

(source
 (github Software-Deployed/server-reason-react-starter))

(authors "Brian Kaplan <brian@softwaredeployed.com>")

(license MIT)

(using melange 0.1)

(pin
 (url "git+https://github.com/ml-in-barcelona/server-reason-react.git")
 (package
  (name server-reason-react)))

(pin
 (url "git+https://github.com/reasonml/reason-react.git")
 (package
  (name reason-react)))

(pin
 (url "git+https://github.com/reasonml/reason-react.git")
 (package
  (name reason-react-ppx)))

(package
 (name server-reason-react-starter)
 (synopsis "Native Reason React Starter")
 (description
  "Starter for server rendered Reason React components with server-reason-react")
 (depends
  (ocaml
   (= "5.4.0"))
  dream
  lwt
  melange
  ocaml-lsp-server
  ocamlformat
  reason
  melange-webapi
  ppxlib
  reason-react-ppx
  reason-react
  server-reason-react)
 (allow_empty)
 (tags
  ("ssr" "reason" "react" "dream")))

; See the complete stanza docs at https://dune.readthedocs.io/en/stable/reference/dune-project/index.html
