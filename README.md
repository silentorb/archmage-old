# Archmage

Multi-project management tool

Archmage allows you to manage multiple projects across multiple Git repositories with interwoven dependencies.  It was primarily designed to support C++ development but can be used  for other languages too.

Archmage has the following features:

### Local Package Manager

Unlike traditional package managers which rely on global remote registries, Archmage uses local registries.  While this can mean more work maintaining a registry, it allows for specialized registries for projects and groups of projects.  Archmage contains tools to manage registries through Git to allow versioned storage and sharing of registries.

Also unlike traditional package managers which are normally focused on supporting package consumers, Archmage is designed to equally support package consumption and development.

Archmage only downloads projects into local folders.  It does not have any form of global installation.

### Versioning

Like any good package manager, Archmage supports robust versioning and dependency version resolution.  It also supports version branching.

### Multi-Repository Management

Archmage contains tools to streamline editing multiple Git repositories at once.  View the status of multiple Git projects and bulk commit, pull, and push.

### Single Project and Multi-Project Repositories

Archmage supports mixing one-project-per-repository and single repositories that contain many sub-projects.  If a project depends on a project housed within a multi-project repository, that entire repository is pulled down.

### Workbenches

Archmage allows the user to create multiple workbenches, each one with different configurations of active projects.

### Third-Party Dependency Abstraction

For large third-party dependencies you will never modify and rarely need to see the source code for, Archmage allows integrating that project into the Archmage workflow while offloading the cloning and compiling into a dependencies directory outside of the active workbench, keeping the usage of the third-party project separate from your own projects.