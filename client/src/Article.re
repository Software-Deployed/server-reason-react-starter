[@react.component]
let make = (~title, ~body, ~last_updated) => {
  <article
    className="bg-gray-50/70 shadow-md rounded-md shadow-black/20 tracking-tighter border-white border-2">
    <h2
      className="m-2 p-1 text-2xl font-thin my-2 text-gray-400 text-shadow-gray-400/50 text-shadow-md">
      {React.string(title)}
    </h2>
    <blockquote className="m-2 p-1 font-normal">
      {React.string(body)}
    </blockquote>
    <footer className="w-full bg-gray-400/20 text-right">
      <span className="text-xs font-extralight mx-1">
        {"Last updated:" ++ last_updated |> React.string}
      </span>
    </footer>
  </article>;
};
