# RoboLib

Simple framework for composing robot control systems from modular C++
components. The application loads a JSON configuration that declares
which components should be started on a given machine. A small
`redis-server` instance is launched as its own component so all child
processes can communicate through Redis.

## Build

```bash
./scripts/build.sh
```

The build requires `redis-server` and `libhiredis-dev` to be installed
on the system.

## Run

After building, launch the `robot` binary. By default it loads
`config.json` in the repository root, but you can specify a different
configuration file as an argument.

```bash
./scripts/run.sh [config.json]
```

While running, press <enter> to quit.

## Configuration Example

```json
{
  "motors": [1, 2],
  "scheduler": true
}
```

This starts two motor components and a simple scheduler alongside the
main controller and the database component.
