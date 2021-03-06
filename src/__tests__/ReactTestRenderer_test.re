open Jest;

external toObject : ReactTestRenderer.t => _ = "%identity";

describe("reactTestRenderer", () => {
  open ExpectJs;

  test("create returns ReactTestInstance", () => {
    let component = ReactTestRenderer.create(<Tester />);

    expect(toObject(component)) |> toContainProperties(
      [|
        "_Scheduler",
        "root",
        "toJSON",
        "toTree",
        "update",
        "unmount",
        "unstable_flushSync",
        "getInstance"
     |]
    );
  });

  test("toJSON returns test rendered JSON", () => {
    let component = ReactTestRenderer.create(<Tester />);
    let json = ReactTestRenderer.toJSON(component);
    let expected = Js.Json.parseExn({|
      {
        "type": "div",
        "props": {},
        "children": [ "Tester" ]
      }
    |});

    expect(json) |> toEqual(expected);
  });
});
