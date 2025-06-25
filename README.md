# RoboLib

Example framework for robot components communicating over TCP.

## Build

```bash
./scripts/build.sh
```

## Run

Start the main controller first. It will keep running and periodically
attempt to connect to any components that are not yet available.

```bash
./scripts/run_main.sh
```

In separate terminals start any components you wish to run:

```bash
./scripts/run_motor1.sh
./scripts/run_motor2.sh
./scripts/run_sensor.sh
```

The new architecture uses a single `robot` executable driven by a JSON
configuration file. Run `./build/robot <config>` where `<config>` defaults to
`config.json`. The file specifies component names, whether to start the Redis
database component, and the port used by Redis.

This demonstrates communication between the main process and each component.

Each component stays active in its own loop waiting for commands from the
controller. The main loop polls the components continuously and occasionally
changes motor positions to verify everything is still connected.
