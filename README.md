# RoboLib

Simple framework for building robots from modular components. Every
component communicates through a small in process database managed by
`DatabaseComponent`. Configuration is loaded from a JSON file so the
same executable can be reused on many machines.

## Build

```bash
./scripts/build.sh
```

## Run

After building, run the project by providing a configuration file:

```bash
./scripts/run.sh configs/example.json
```

This will start the main controller along with any components defined in
`example.json`.
