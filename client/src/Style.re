[@platform js]
module Client = {
  [@mel.module "../../client/src/index.css"] external _css: unit = "default";
};

[@platform native]
module Client = {};
