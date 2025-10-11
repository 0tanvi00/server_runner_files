package main

import (
    "fmt"
    "net/http"
    "os/exec"
)

func main() {
    http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
        callPythonScript()
        fmt.Fprintln(w, "Go server is running!")
    })

    fmt.Println("Server is running on http://localhost:3000")
    http.ListenAndServe(":3000", nil)
}

func callPythonScript() {
    cmd := exec.Command("python", "test.py")
    output, err := cmd.CombinedOutput()
    if err != nil {
        fmt.Printf("Error from Python script: %v\n", err)
    }
    fmt.Printf("Python script output: %s\n", output)
}
