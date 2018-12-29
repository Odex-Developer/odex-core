# Masternode Commands

`systemctl start odexd`
\- Starts the Odex Daemon

`systemctl stop odexd`
\- Stops the Odex Daemon

`systemctl restart odexd`
\- Restarts the Odex Daemon

`systemctl status odexd`
\- Displays the status of the Odex Daemon

`odex-cli masternode status`
\- Displays the status of the Odex masternode running on the VPS

`odex-cli getinfo`
\- Displays general info about the masternode

`odex-cli masternodecurrent`
\- Displays additional info about the masternode

`ps aux | grep odex`
\- Shows if the odexd process is running

`dmesg | egrep -i 'killed process'`
\- Lets you know whether odexd was killed due to lack of memory

`nano ~/.odex/odex.conf`
\- Edits your odex.conf file

`killall -9 odexd`
\- Force quits odexd (*USE WITH CAUTION*)

`odex-cli getpeerinfo | grep synced_headers`
\- Displays synced headers

`odex-cli getmasternodecount`
\- Displays count of all masternodes

`bash <( curl https://raw.githubusercontent.com/odex-crypto/Odex-MN-Install/master/refresh_node.sh )`

Refreshes your node by clearing the chaindata

`bash <( curl https://raw.githubusercontent.com/odex-crypto/Odex-MN-Install/master/update_node.sh )`

Updates your node to the newest version
