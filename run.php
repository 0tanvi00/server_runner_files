<?php
$port = 3000;
$address = "localhost";

echo "PHP server is running on http://$address:$port\n";

if (php_sapi_name() == "cli-server") {
    callPythonScript();
    echo "PHP server is running!\n";
}

function callPythonScript() {
    $output = [];
    $return_var = 0;
    exec("python test.py 2>&1", $output, $return_var);

    foreach ($output as $line) {
        echo "Python script output: $line\n";
    }
    echo "Python script exited with code $return_var\n";
}
?>
