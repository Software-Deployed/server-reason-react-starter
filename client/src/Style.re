[@platform js]
module Client = {
  [@mel.module "./index.css"] external _css: unit = "default";
};

[@platform native]
module Client = {};
