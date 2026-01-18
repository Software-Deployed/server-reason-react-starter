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
  <Document>
    <div className="border border-gray-400">
      {React.string("Found " ++ Int.to_string(count) ++ " articles")}
    </div>
  </Document>;
};
