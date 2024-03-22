<!--
SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
SPDX-License-Identifier: CC0-1.0
-->

# SeqAn App Template [![build status][1]][2] [![codecov][3]][4]
<!--
    Above uses reference-style links with numbers.
    See also https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet#links.

    For example, `[![build status][1]][2]` evaluates to the following:
        `[link_text][2]`
        `[2]` is a reference to a link, i.e. `[link_text](https://...)`

        `[link_text]` = `[![build status][1]]`
        `[1]` is once again a reference to a link - this time an image, i.e. `[![build status](https://...)]
        `![build status]` is the text that should be displayed if the linked resource (`[1]`) is not available

    `[![build status][1]][2]` hence means:
    Show the picture linked under `[1]`. In case it cannot be displayed, show the text "build status" instead.
    The picture, or alternative text, should link to `[2]`.
-->

<!--
    This is the CI badge image:
        `https://img.shields.io/github/workflow/status/` - we do not use GitHub's badges as they are not customisable.
        `/seqan/app-template/` - owner/repository
        `CI%20on%20Linux` - name of the workflow as encoded URL (e.g., whitespace = %20)
        `master` - branch to show
        `?style=flat&logo=github` - use a GitHub-style badge
        `&label=App-Template%20CI` - text on the badge
        `"Open GitHub actions page"` - this text will be shown on hover
-->
[1]: https://img.shields.io/github/actions/workflow/status/seqan/app-template/ci_linux.yml?branch=main&style=flat&logo=github&label=App-Template%20CI "Open GitHub actions page"
<!--
    This is the CI badge link:
        `https://github.com/seqan/app-template/actions` - actions page of owner(seqan)/repository(app-template)
        `?query=branch%3Amaster` - only show actions that ran on the mater branch
-->
[2]: https://github.com/seqan/app-template/actions?query=branch%3Amain
<!--
    This is the Codecov badge image:
        Codecov offers badges: https://app.codecov.io/gh/seqan/app-template/settings/badge
        While being logged in into Codecov, navigate to Settings->Badge and copy the markdown badge.
        Copy the image part of the markdown badge here.
    `"Open Codecov page"` - this text will be shown on hover
-->
[3]: https://codecov.io/gh/seqan/app-template/branch/master/graph/badge.svg?token=V82JRCXF0K "Open Codecov page"
<!--
    This is the Codecov badge link:
        Codecov offers badges: https://app.codecov.io/gh/seqan/app-template/settings/badge
        While being logged in into Codecov, navigate to Settings->Badge and copy the markdown badge.
        Copy the URL part of the markdown badge here.
-->
[4]: https://codecov.io/gh/seqan/app-template

This is a template for C++ app developers.
You can easily use this template and modify the existing code to suit your needs.
It provides an elementary CMake set-up, some useful SeqAn libraries, and an example application.

For requirements, check the [Software section of the SeqAn3 Quick Setup](https://docs.seqan.de/seqan3/main_user/setup.html#autotoc_md109).

## Instructions for App Developers:

If you want to build an app, do the following:

0. You need to be signed in with a **GitHub account**.
1. <details><summary>Press the <code>Use this template</code>-Button to create your <b>own repository</b>.</summary><br>

   Screenshot TODO
   </details>
2. **Clone** your repository locally: `git clone git@github.com:max/my-repo-name.git`

Note: The subsequent steps are not necessary but a recommendation and quick setup.

3. <details><summary>Adapt the project name in <code>my-repo-name/CMakeLists.txt</code>, e.g., from <code>app-template</code> to <code>MyDragonApp</code></summary><br>

   The project name is defined in these lines:

   ```cmake
   project (app-template
            LANGUAGES CXX
            VERSION 1.0.0
            DESCRIPTION "My application description"
   )
   ```

   Change it e.g. to this:

   ```cmake
   project (MyDragonApp
            LANGUAGES CXX
            VERSION 1.0.0
            DESCRIPTION "Let dragons fly"
   )
   ```
   </details>
4. <details><summary>Build and test the app (example) </summary><br>

    Next to your local repository clone (e.g. `my-repo-name`), you can do the following to build and test your app:

    ```bash
    mkdir build           # create build directory
    cd build              # step into build directory
    cmake ../my-repo-name # call cmake on the repository
    make                  # build the app MyDragonApp
    make check            # build and run tests *1
    ./bin/MyDragonApp     # Execute the app (prints a short help page)
    ```
   </details>
<!-- 8. optional: publish your tool to the galaxy toolshed, follow the example in https://github.com/SGSSGene/raptor-galaxy -->

## Instructions for SeqAn3 Tutorial Purposes:

If you just want some hands-on experience with SeqAn Libraries or a quick setup for our tutorials, do the following:

1. Clone this repository: `git clone https://github.com/seqan/app-template.git`
2. Create a build directory and visit it: `mkdir build && cd build`
3. Run CMake: `cmake ../app-template`
4. Build the application: `make`
5. Try executing the app: `./bin/app-template`

You can now start your hands-on experience by looking at or editing the file `src/main.cpp`.

### Adding a new cpp file

If you want to add a new cpp file (e.g., tutorial1.cpp) that is compiled and linked with the current infrastructure, do the following:

1. Create a new file `tutorial1.cpp` in the `src/` directory.
   <details><summary>The file content could look like this:</summary><br>
       
   ```cpp
   #include <seqan3/core/debug_stream.hpp>

   int main()
   {
       seqan3::debug_stream << "Hello, World!" << std::endl;
   }
   ```
   </details>
2. Add the following lines at the bottom of `src/CMakeLists.txt`
    ```cmake
    # Add another cpp file.
    add_executable (tutorial01 tutorial01.cpp)
    target_link_libraries (tutorial01 PRIVATE "${PROJECT_NAME}_lib")
    ```
3. Go to the build directory `cd build`
4. Refresh CMake `cmake .`
5. Build your new cpp file `make tutorial01`
6. Execute your new binary with `./tutorial01`
