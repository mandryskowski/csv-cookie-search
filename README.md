# csv-cookie-search
A parser of cookies in csv format which allows you to find the most active cookies on a certain date.
# Building
Requires CMake 3.14 or higher.

```
cmake -B build/ -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build/ --config Release
```

# Usage

```
cd build/src
./CookieSearch -f <path_to_file> -d <date_in_utc>
```

# Testing
Using [GoogleTest](https://github.com/google/googletest), which will be installed by CMake.
```
cd build/test
./test
```
