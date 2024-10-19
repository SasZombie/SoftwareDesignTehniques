g++ server.cpp cpp/strategy.cpp cpp/observer.cpp cpp/proxy.cpp cpp/context.cpp cpp/factory.cpp -std=c++23 -o build/server -Wall -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith -Wmissing-declarations -Winline -Wundef -Wcast-qual -Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal -pedantic -fsanitize=address -fsanitize=leak
g++ client.cpp -std=c++23 -o build/client -Wall -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith -Wmissing-declarations -Winline -Wundef -Wcast-qual -Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal -pedantic -fsanitize=address -fsanitize=leak