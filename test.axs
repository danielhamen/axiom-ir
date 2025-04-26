func print() {
    Meta.Emit("(TIME)");
    Meta.Write();
    Meta.Emit("(PUSH, \"\\n\")");
    Meta.Write();
    Meta.Dump();
    Meta.Flush();
}

print();
