<?php

    // configuration
    require("../includes/config.php"); 

    // select all the users transaction history
    $rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);

    // create the history associative array for the template to
    // loop through for display of history information.
    $histories = [];
    foreach ($rows as $row)
    {
        $histories[] = [
            "transaction" => $row["transaction"],
            "date" => $row["datetime"],
            "symbol" => $row["symbol"],
            "shares" => $row["shares"],
            "price" => $row["price"]
        ];
    }

    // render portfolio
    render("history.php", ["histories" => $histories, "title" => "History"]);

?>
