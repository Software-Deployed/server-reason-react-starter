include Style.Client;

[@react.component]
let make = (~articles) => {
  let count = articles |> List.length;
  <div>
    {React.string("Found " ++ Int.to_string(count) ++ " articles")}
  </div>;
};
