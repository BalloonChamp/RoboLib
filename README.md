# RoboLib

Example framework for robot components communicating over TCP.

## Build

```bash
./scripts/build.sh
```

## Run

Start the main controller first. It will warn if a component is not yet
available but continues running.

```bash
./scripts/run_main.sh
```

In separate terminals start any components you wish to run:

```bash
./scripts/run_motor1.sh
./scripts/run_motor2.sh
./scripts/run_sensor.sh
```

This demonstrates communication between the main process and each component.

