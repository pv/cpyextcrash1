import sys
import threading
import time

import testmodule


def main():
    def worker():
        try:
            testmodule.run_test()
        except:
            pass

    print(sys.version)

    for j in range(10):
        threads = [threading.Thread(target=worker)
                   for k in range(40)]
        for t in threads:
            time.sleep(0.05)
            t.start()
        for t in threads:
            t.join()

    print("OK")

if __name__ == "__main__":
    main()
