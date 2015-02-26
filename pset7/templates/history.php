<div>
<table class="table table-striped">
    <thead>
        <tr>
            <th>Transaction</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>
    <tbody>
    <?php foreach ($histories as $history): ?>

        <tr>
            <td><?= $history["transaction"] ?></td>
            <td><?= $history["date"] ?></td>
            <td><?= $history["symbol"] ?></td>
            <td><?= $history["shares"] ?></td>
            <td><?= $history["price"] ?></td>
        </tr>

    <?php endforeach ?>
    </tbody>
</table>
</div>

