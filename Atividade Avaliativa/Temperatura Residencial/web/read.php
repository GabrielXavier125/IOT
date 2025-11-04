<?php
$arquivo = "dados.txt";

if (file_exists($arquivo)) {
    echo trim(file_get_contents($arquivo));
} else {
    echo "--";
}
?>
