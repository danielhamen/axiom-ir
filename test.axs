namespace Time {}
namespace Logging {}
namespace Path {}
namespace Threading {}
namespace RegEx {}
namespace JSON {}
namespace XML {}
namespace Image {}
namespace Audio {}
namespace Video {}
namespace Color {}
namespace Environment {}
namespace Console {}
namespace Network {}
namespace Math {}

let x = 3;
let y = x.toString();

Meta.Emit("(WRITE, $x)");
Meta.Emit("(WRITE, \"\\n\")");
Meta.Emit("(DUMP)");
Meta.Emit("(FLUSH)");

Meta.Emit("(WRITE, $y)");
Meta.Emit("(WRITE, \"\\n\")");
Meta.Emit("(DUMP)");
Meta.Emit("(FLUSH)");

Meta.Emit("(LIST_NEW)");
Meta.Emit("(PUSH, 10)");
Meta.Emit("(PUSH, 0)");
Meta.Emit("(LIST_INS)");
Meta.Emit("(LIST_LEN)");
Meta.Emit("(WRITE)");
Meta.Emit("(DUMP)");
Meta.Emit("(FLUSH)");
