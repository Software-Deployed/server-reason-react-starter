[@platform js]
module Style = {
  [%%raw "import \"./index.css\""];
};

[@platform native]
module Style = {
  let _css = ();
};

[@react.component]
let make = (~articles) => {
  let count = articles |> List.length;
  <div
    className="border-white border bg-gray-400/50 p-8 max-w-xl mx-auto rounded-md shadow-gray-200/50 shadow-md font-semibold tracking-wider">
    <h1
      className="font-thin text-6xl text-shadow-md text-shadow-gray-200/50 text-gray-200 text-center">
      {"Example Server Rendered Reason React Blog" |> React.string}
    </h1>
    <p className="text-gray-200 py-4">
      {React.string("Found " ++ Int.to_string(count) ++ " articles")}
    </p>
    {articles
     |> List.map(((_id, title, body, last_updated, _created_at)) =>
          <Article title body last_updated />
        )
     |> Array.of_list
     |> React.array}
  </div>;
};
