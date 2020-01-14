
# ./spr.sh <n> <events> <queries>
make dc
make check
for blocks in {1..8}
{
    echo $blocks blocks
    for seed in {1..1000}
    {
        ./gen $1 $2 $3 $blocks $seed >test.in
        if [ $? -eq 1 ]; then
            echo "went wrong"
            break
        fi

        ./brute <test.in >brute.out
        ./dc <test.in >dc.out
        diff brute.out dc.out || cat -
    }
}