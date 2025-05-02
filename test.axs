namespace Time {
    func time() {
        Meta.Time();
        let _t = 3;
        Meta.Pop(_t);
        return _t;
    }
}

namespace System {
    namespace IO {
        func print() {
            return nil;
        }
    }
}

System.IO.print();
