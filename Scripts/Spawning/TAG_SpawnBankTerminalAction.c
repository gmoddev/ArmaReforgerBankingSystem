class TAG_SpawnBankTerminalAction : ScriptedUserAction
{
    override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
    {
        vector position = "0 0 0";
        TAG_BankTerminal bankTerminal = TAG_BankTerminal.Cast(GetGame().CreateEntity("TAG_BankTerminal", position));

        // WIP handle logic
    }
};