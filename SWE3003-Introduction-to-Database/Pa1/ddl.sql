CREATE TABLE "user"(
    id  VARCHAR(12) UNIQUE NOT NULL,
    password VARCHAR(16) NOT NULL,
    admin BOOLEAN NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE item(
    id INTEGER UNIQUE NOT NULL,
    description VARCHAR(100),
    category VARCHAR(15) NOT NULL,
    condition VARCHAR(10) NOT NULL,
    seller VARCHAR(12) NOT NULL,
    status BOOLEAN, -- 1: opened, 0: closed
    PRIMARY KEY (id),
    FOREIGN KEY (seller)  REFERENCES "user" (id) ON DELETE CASCADE ON UPDATE CASCADE,
    CHECK ( category IN ('Electronics', 'Books', 'Home', 'Clothing', 'Sporting Goods', 'Others')),
    CHECK ( condition IN ('New', 'Like-new', 'Good', 'Acceptable'))
);

CREATE TABLE bid(
    item_id INTEGER UNIQUE NOT NULL,
    bid_price INTEGER,
    bid_time TIMESTAMP,
    bin_price INTEGER NOT NULL,
    bidder VARCHAR(12),
    close TIMESTAMP NOT NULL,
    post TIMESTAMP NOT NULL,
    FOREIGN KEY (item_id)   REFERENCES item(id) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (bidder)   REFERENCES "user"(id) ON DELETE SET NULL ON UPDATE CASCADE
);

CREATE TABLE billing(
    item_id INTEGER UNIQUE NOT NULL,
    date TIMESTAMP NOT NULL,
    seller VARCHAR(12) NOT NULL,
    buyer VARCHAR(12),
    price INTEGER,
    FOREIGN KEY (item_id) REFERENCES item(id) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (seller) REFERENCES "user"(id) ON UPDATE CASCADE,
    FOREIGN KEY (buyer) REFERENCES "user"(id) ON UPDATE CASCADE
);

CREATE TABLE bid_log(
    user_id VARCHAR(12) NOT NULL,
    item_id INTEGER NOT NULL,
    price INTEGER NOT NULL,
    bid_time TIMESTAMP NOT NULL,
    FOREIGN KEY (user_id) REFERENCES "user"(id) ON UPDATE CASCADE,
    FOREIGN KEY (item_id) REFERENCES item(id) ON UPDATE CASCADE
);

-- commission fee
CREATE OR REPLACE FUNCTION comm_fee(INTEGER)
RETURNS INTEGER AS $$
    BEGIN
        RETURN $1 / 10;
    END;
$$ LANGUAGE plpgsql;

-- Sell function
CREATE OR REPLACE FUNCTION Sell(VARCHAR, VARCHAR, VARCHAR, VARCHAR, INTEGER, TIMESTAMP) 
-- username, description, category, condition, bin_price, close_date
RETURNS VOID AS $$
    DECLARE
        count INTEGER;
    BEGIN
        SELECT count(*) INTO count FROM item;
        INSERT INTO item VALUES(count, $2, $3, $4, $1, TRUE);
        INSERT INTO bid VALUES(count, 0, NULL, $5, NULL, $6, NOW());
    END;
$$ LANGUAGE  plpgsql;

-- Buy function
CREATE OR REPLACE FUNCTION Buy(VARCHAR, INTEGER, INTEGER) -- username, item_id, price
RETURNS INTEGER AS $$
    DECLARE
        binp INTEGER := 0;
        bidp INTEGER;
        sellerID VARCHAR(12);
    BEGIN
        SELECT bid_price, bin_price INTO bidp, binp FROM bid WHERE item_id=$2;
        IF binp is null THEN -- no exist item id
            RETURN -1;
        END IF;
        IF binp <= $3 THEN
            UPDATE item SET status=FALSE WHERE id=$2; -- item bidding close

            SELECT seller INTO sellerID FROM item WHERE id=$2;
            INSERT INTO billing VALUES($2, NOW(), sellerID, $1, binp); -- insert into billing(closed items)

            DELETE FROM bid WHERE item_id=$2; -- delete from bid(opened items)

            INSERT INTO bid_log VALUES($1, $2, binp, NOW());

            RETURN 1;
        ELSEIF bidp < $3 THEN
            UPDATE bid SET bid_price=$3, bid_time=NOW(), bidder=$1 WHERE item_id=$2;

            INSERT INTO bid_log VALUES($1, $2, $3, NOW());
            RETURN 2;
        ELSE
            RETURN 0;
        END IF;
    END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION Update_bid()
RETURNS VOID AS $$
    DECLARE
        closed_item RECORD;
    BEGIN
        FOR closed_item IN SELECT * FROM bid JOIN item ON bid.item_id=item.id WHERE item.status=TRUE AND bid.close <= NOW()
        LOOP
            UPDATE item SET status=FALSE WHERE id=closed_item.id;
            DELETE FROM bid WHERE bid.item_id=closed_item.id; 
            INSERT INTO billing VALUES(closed_item.id, closed_item.close, closed_item.seller, closed_item.bidder, closed_item.bid_price);
        END LOOP;
    END;
$$ LANGUAGE plpgsql;