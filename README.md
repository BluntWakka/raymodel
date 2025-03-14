# PERTINENT INFORMATION

Project is written in C++ and uses a dockerfile to create the proper environment to compile.
Be warned, docker alone does not suffice to run properly as the SDL library needs a GPU resource to generate anything,
meaning that you will need to execute in an environment that provides this resource.

When running on command line, there is one extra option to chnge the "stopper" body to a strangley shaped one (oblong).
To change to the strange shape, simply add the charatcer 's' when executing as an argument.