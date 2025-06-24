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

These scripts now launch a single `robot` binary with different flags
so you can also invoke it manually. For example `./build/robot --motor 1`
starts the first motor component while `./build/robot --main` starts the
controller loop. The main loop accepts optional `--motor-port <p>` and
`--sensor-port <p>` flags which can be repeated to configure additional
components.

This demonstrates communication between the main process and each component.

Each component stays active in its own loop waiting for commands from the
controller. The main loop polls the components continuously and occasionally
changes motor positions to verify everything is still connected.
