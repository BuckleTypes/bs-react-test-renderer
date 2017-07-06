open Jest;
open ExpectJs;

external toObject :
  option ReasonReact.reactElement => Js.t {..} = "%identity";

let element = {
  "type": "div",
  "key": Js.null,
  "ref": Js.null,
  "props": Js.Obj.empty (),
  "_owner": Js.null,
  "_store": Js.Obj.empty (),
};

let _ =

describe "reactShallowRenderer" (fun _ => {
  test "createRenderer" (fun _ => {
    let renderer = ReactShallowRenderer.createRenderer ();

    expect (Js.Undefined.return renderer) |> toBeDefined;
  });

  test "render accepts renderer" (fun _ => {
    let renderer = ReactShallowRenderer.createRenderer ();
    let render = ReactShallowRenderer.render renderer;

    expect (Js.typeof render) |> toBe "function";
  });

  test "render will render a component" (fun _ => {
    let renderer = ReactShallowRenderer.createRenderer ();
    let component = ReactShallowRenderer.render renderer <Tester /> |> toObject;

    expect component |> toMatchObject element;
  });

  test "renderWithRenderer will render a component" (fun _ => {
    let component = ReactShallowRenderer.renderWithRenderer <Tester /> |> toObject;

    expect component |> toMatchObject element;
  });

  test "getRenderOutput returns element" (fun _ => {
    let renderer = ReactShallowRenderer.createRenderer ();

    let _ = ReactShallowRenderer.render renderer <Tester />;

    let component = ReactShallowRenderer.getRenderOutput renderer |> toObject;

    expect component |> toMatchObject element;
  });

  test "unmount removes the node" (fun _ => {
    let renderer = ReactShallowRenderer.createRenderer ();

    let _ = ReactShallowRenderer.render renderer <Tester />;
    ReactShallowRenderer.unmount renderer;

    let component = ReactShallowRenderer.getRenderOutput renderer |> toObject;

    expect (Js.Null.return component) |> toBeNull;
  });
});
